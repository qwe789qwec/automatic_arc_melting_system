import streamlit as st
from streamlit_sortables import sort_items

original_items = [
    {'header': 'This_runs', 'items': 
     ["slider init cobotta init weighing init plc init",
    "slider1 cup_stock_r",
    "cobotta take_cup_from_stock"],},
    {'header': 'choose from here', 'items':
    ["slider init cobotta init weighing init plc init",
    "slider1 cup_stock_r",
    "cobotta take_cup_from_stock"]}
]

sorted_items=sort_items(original_items, multi_containers=True, direction='vertical')
#st.write(f'sorted_items: {sorted_items}')

st.write('Hello')