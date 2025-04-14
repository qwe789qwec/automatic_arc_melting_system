import streamlit as st
import pandas as pd
from pymatgen.core import Composition
import pymatgen.core as mg
import json

st.set_page_config(layout='wide')

# Auxiliary functions
def get_molarmass(formula):
    return float(Composition(formula).weight)

def masscalc(formula, target_mass):
    mass = get_molarmass(formula)
    mol = target_mass / mass
    composition = Composition(formula)
    value_dic = composition.as_dict()
    original_mass = {key: get_molarmass(key) * value * mol for key, value in value_dic.items()}
    return original_mass

def get_melting_point(element_symbol):
    try:
        element = mg.Element(element_symbol)
        return element.melting_point if element.melting_point is not None else 0.0
    except KeyError:
        return None

def load_from_stock_file():
    try:
        with open("stock.txt", "r") as file:
            return json.load(file)
    except FileNotFoundError:
        print("stock.txt not found")
        return {}

def query_stock(element_name):
    reverse_position = load_from_stock_file()
    for position, element in reverse_position.items():
        if element == element_name:
            return tuple(map(int, position.strip("()").split(", ")))  # (行, 列) の形式に変換
    return "Input atom is not in the stock"




tab1, tab2 = st.tabs(['setting','execute'])
with tab1:
    # Manual input using GUI
    with st.sidebar:
        st.header("Input Parameters")
        target_composition = st.text_input("Target Composition", key="composition")
        target_weight = st.number_input("Target weight (g)", value=0.5, step=0.1, format="%.2f")
        
        weighing_order = st.selectbox("Weighing_order, note that first element goes bottom",
                                    ["melting_point","As_input","Alphabetical"], index=0)
        
        flip_times = st.selectbox("How many times of flips?",
                                    ["2","3","4","5"], index=1)
        
        arc_path = st.selectbox("Arc_path",
                                    ["1","2","3"], index=2)
        arc_discharge_power = st.selectbox("Arc_discharge_power",
                                           [10,15,20,25,30,35,40,45,50],index=2)

    col1, col2 = st.columns(2)
    # Right column: Display stock matrix
    with col2:
        st.subheader("Stock Layout")
        
        # Load and process stock data
        stock_data = load_from_stock_file()
        
        # Create empty 3x5 matrix
        matrix = [['' for _ in range(5)] for _ in range(3)]
        
        # Fill matrix with elements from stock data
        for pos, element in stock_data.items():
            # Convert string "(row, col)" to integers
            row, col = eval(pos)
            # Adjust to 0-based indexing
            matrix[row-1][col-1] = element
        
        # Create a DataFrame for better display
        df = pd.DataFrame(
            matrix,
            index=['1', '2', '3'],  # Row numbers starting from 1
            columns=['1', '2', '3', '4', '5']  # Column numbers starting from 1
        )
        
        # Style the DataFrame
        def style_cells(val):
            if val == '':
                return 'background-color: #f0f0f0'
            return 'background-color: #90EE90'
        
        styled_df = df.style.applymap(style_cells)
        
        # Display the matrix
        st.dataframe(styled_df, use_container_width=True)

    if target_composition:
        mass_raw_atoms = masscalc(target_composition, target_weight)
        
        # Create a list to hold tuples of (element, mass, melting_point)
        elements_info = []
        input_order_elements = list(mass_raw_atoms.keys()) # Capture input order
        
        for element, mass in mass_raw_atoms.items():
            melting_point = get_melting_point(element)
            elements_info.append((element, mass, melting_point))

        # Sort by inverse melting point
    # Sorting logic
        if weighing_order == "melting_point":
            sorted_elements = sorted(elements_info, key=lambda item: item[2] if item[2] is not None else float('inf'), reverse=False)
        elif weighing_order == "Alphabetical":
            sorted_elements = sorted(elements_info, key=lambda item: item[0]) # Sort by element symbol (alphabetical)
        elif weighing_order == "As_input":
            as_input_order_dict = {element: index for index, element in enumerate(input_order_elements)}
            sorted_elements = sorted(elements_info, key=lambda item: as_input_order_dict[item[0]]) # Sort by input order
        # Prepare output
        output_data = {element: {"mass": mass, "melting_point": melting_point} for element, mass, melting_point in sorted_elements}

        # Output the sorted dictionary
        # st.write(output_data)
        # Create two columns for display

        # Left column: Display output_data
        with col1:
            st.subheader("Composition Details")
            st.write(output_data)

    steps_content = """slider init cobotta init weighing init plc init
    slider1 cup_stock_r
    cobotta take_cup_from_stock
    weighing open slider1 weight_pos
    cobotta put_cup_to_weight"""
    if target_composition:
        for element in output_data:
            mass = output_data[element]['mass']
            miligram = round(float(mass)*1000,1)
            position = query_stock(element)
            if position != "Input atom is not in the stock":
                cobotta_position, slider_position = position
                steps_content += " \n"
                steps_content += f"slider1 shelf{slider_position} weighing close\n"
                steps_content += f"cobotta take_dose_from_shelf{cobotta_position}\n"
                steps_content += "slider1 weight_pos weighing open\n"
                steps_content += "cobotta put_dose_to_weight\n"
                steps_content += f"weighing mgram{miligram:.1f}\n"
                steps_content += "cobotta take_dose_from_weight\n"
                steps_content += f"slider1 shelf{slider_position} weighing close\n"
                steps_content += f"cobotta put_dose_to_shelf{cobotta_position}\n"
        
        steps_content += " \n"
        steps_content += "cobotta take_cup_from_weight plc vent\n"
        steps_content += "weighing close slider1 pos1\n"
        steps_content += "cobotta put_cup_to_arc plc gateOpen\n"
        steps_content += "plc checkValve\n"
        steps_content += "slider put_cup_arc\n"
        steps_content += "plc gateClose\n"
        steps_content += "plc pump\n"
        steps_content += "slider arcinit\n"

        for i in range(int(flip_times)+1):
            if i% 2 == 0:
                direction = "cw"
            else:
                direction = "ccw"
            steps_content += " \n"
            steps_content += "plc buzz\n"
            steps_content += "plc arcOn\n"
            steps_content += f"slider arc_{direction}_{arc_path}\n"
            steps_content += "plc arcOff\n"
            steps_content += "plc wait20s\n"
            if i != int(flip_times):
                steps_content += "plc autoFlip\n"
            else:
                steps_content += " \n"
                steps_content += "plc vent slider pos1\n"
                steps_content += "plc gateOpen\n"
                steps_content += "plc checkValve\n"
                steps_content += "slider take_cup_arc\n"
                steps_content += "plc gateClose cobotta take_cup_from_arc\n"
                steps_content += "slider1 weight_pos weighing open\n"
                steps_content += "plc singlePump cobotta put_cup_to_weight\n"
                steps_content += "weighing close\n"

    if st.button('Make steps.txt'):
        with open('steps.txt', 'w') as f:
            f.write(steps_content)
            st.success('steps.txt has been created!')    
            st.code(steps_content)

    if st.button('Make testrun'):
        steps_content = """slider init cobotta init weighing init plc init
        slider1 cup_stock_r
        plc buzz
        slider1 pos1"""
        with open('/home/song/Documents/ww/automatic_arc_melting_system/src/main_process/src/steps.txt', 'w') as f:
            f.write(steps_content)
            st.success('/home/song/Documents/ww/automatic_arc_melting_system/src/main_process/src/steps.txt has been created!')    
            st.code(steps_content)

    # In case it loads from input.csv
    # @st.cache_data
    # def load_input(inputcsv):
    #     df = pd.read_csv(inputcsv)
    #     return df
    # input_csv = load_input('./input.csv')
    # st.write(input_csv)

with tab2:
    import subprocess
    import os
    import time
    import signal

    # Define functions to run your scripts
    def run_script():
        # Change to your script directory
        # os.chdir('/path/to/your/script')
        subprocess.Popen(['.', 'install/setup.bash'])
        subprocess.Popen(['ros2', 'launch', 'launch/launch_instruments.py'])

    # Initialize session state for processes
    if 'processes' not in st.session_state:
        st.session_state.processes = []

    def run_ros2():
        # Combined command to source environment and run ROS2 node in one shell
        command = (
            'bash -c "source /home/song/Documents/ww/automatic_arc_melting_system/install/setup.bash && '
            'ros2 run main_process MainProcess"'
        )
        process = subprocess.Popen(
            command,
            shell=True,
            preexec_fn=os.setsid  # Create new process group
        )
        st.session_state.processes.append(process)
        st.write("ROS2 process started with PID:", process.pid)

    def stop_processes():
        # Terminate processes using their process groups
        for process in st.session_state.processes:
            if process.poll() is None:  # Check if still running
                try:
                    os.killpg(os.getpgid(process.pid), signal.SIGTERM)
                except ProcessLookupError:
                    pass  # Process already terminated
        st.session_state.processes.clear()
        st.write("All processes terminated")

    # Streamlit interface
    st.title("Run automatic arc-melting synthesis")

    check1 = st.checkbox("Water running?       (水冷on)")
    check2 = st.checkbox("Arc power supply on? (アーク電源on)")
    check3 = st.checkbox("Camera ready?        (カメラ用意)")
    check4 = st.checkbox("Recording ready?     (記録用意)")
    check5 = st.checkbox("Raw material enough? (原料は充分か)")

    if check1 & check2 & check3 & check4 & check5:
        if 'button_clicked' not in st.session_state:
            st.session_state.button_clicked = False

        if 'confirmation_clicked' not in st.session_state:
            st.session_state.confirmation_clicked = False

        def process_function():
            # Replace this with the process you want to execute
            st.write("Executing the process...")
            st.write("Process completed.")

        def on_button_click():
            st.session_state.button_clicked = True

        def on_confirmation_yes_click():
            st.session_state.confirmation_clicked = True
            st.session_state.button_clicked = False # Reset the state for next use

        def on_confirmation_no_click():
            st.session_state.confirmation_clicked = False
            st.session_state.button_clicked = False # Reset the state for next use


        st.button("Click to Start Process", on_click=on_button_click)
        if st.session_state.button_clicked:
            st.write("Are you sure you want to proceed?")
            # st.button("Yes", on_click=on_confirmation_yes_click)
            # run_script()
            # time.sleep(1)
            if st.button("Start ROS2 Process"):
                run_ros2()
                st.write("ROS2 Process is running!")

            if st.button("Stop All Processes"):
                stop_processes()
            # st.button("No", on_click=on_confirmation_no_click)
        if st.session_state.confirmation_clicked and not st.session_state.button_clicked:
            st.write("Process executed because you pressed 'Yes'.")
            st.session_state.confirmation_clicked = False # Reset confirmation state
        elif st.session_state.button_clicked and not st.session_state.confirmation_clicked:
            st.write("Waiting for your confirmation...")
        elif not st.session_state.button_clicked and not st.session_state.confirmation_clicked:
            st.write("Press 'Click to Start Process' to begin.")

    
    st.write('Below will be executed. Make sure if this is what you want.')
    with open('/home/song/Documents/ww/automatic_arc_melting_system/src/main_process/src/steps.txt', 'r') as f:
        steps=f.read()
        st.code(steps)




