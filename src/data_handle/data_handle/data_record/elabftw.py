from datetime import datetime
import requests
import json
import os
import re

class ElabFTW:
    def __init__(self, api_url, api_key):
        # Set the API URL
        self.api_url = api_url
        # Set the API key
        self.api_key = api_key
        self.headers = {"Authorization": self.api_key, "Content-Type": "application/json"}

        self.metadata_form = {
            "extra_fields": {
                "Date": {"value": " "},
                "number": {"value": 0},  # experiment_id
                "Arc Path": {"value": " "},
                "Weighing Order": {"value": " "},
                "Number of Flips": {"value": " "},
                "Target Quantity": {"value": " "},
                "Target Composition": {"value": " "},
                "Arc Discharge Power": {"value": 40},
                "Total Mass After Arc": {"value": " "},
                "Mass of Product of Arc": {"value": " "},
                "Arc Discharge-path Diameter": {"value": "7000, 4000, 6-2-2 sec"},
                "Weighted Compositional Ratio": {"value": " "},
            }
        }

    def create_experiment(self, composition=None):

        today_str = datetime.now().strftime('%Y%m%d')
        base_pattern = f"{composition}_{today_str}"
    
        response = requests.get(f"{self.api_url}/experiments?limit=100", headers=self.headers, verify=False)
        if response.status_code != 200:
            print("⚠️ 既存experiment取得失敗:", response.status_code)
            return f"{base_pattern}_1"
    
        experiments = response.json()
        numbers = []
        pattern = re.compile(re.escape(base_pattern) + r"_(\d+)$")
        for exp in experiments:
            title = exp.get("title") or ""
            m = pattern.match(title)
            if m:
                numbers.append(int(m.group(1)))
    
        next_number = max(numbers) + 1 if numbers else 1
        
        full_title = f"{composition}_{today_str}_{next_number}"

        response = requests.post(
            f"{self.api_url}/experiments",
            headers=self.headers,
            data=json.dumps({}),
            verify=False
        )
        if response.status_code != 201:
            print("Failed to make new experiment:", response.status_code, response.text)
            return None

        experiment_id = response.headers["Location"].split("/")[-1]
        print(f"New experiment created: ID = {experiment_id}")

        if full_title:
            patch_resp = requests.patch(
                f"{self.api_url}/experiments/{experiment_id}",
                headers=self.headers,
                data=json.dumps({"title": full_title}),
                verify=False
            )
            if patch_resp.status_code == 200:
                print(f"Title updated: {full_title}")
            else:
                print("Failed to update title:", patch_resp.status_code, patch_resp.text)
        self.experiment_id = experiment_id
        self.update_form("Date", today_str)
        self.update_form("Target Composition", composition)
        return experiment_id

    def update_form(self, name, parameter):
        self.metadata_form["extra_fields"][name]["value"] = parameter

    def record_data(self, data):
        print(f"[DEBUG] record_data received: {repr(data)}")  # for debugging

        if data.startswith("slider_arc_cw") or data.startswith("slider_arc_ccw"):
            arc_path = self.metadata_form["extra_fields"]["Arc Path"]["value"]
            if arc_path == " ":
                arc_path = data.split("_")[2]
            else:
                arc_path = f"{arc_path}_{data.split('_')[2]}"
            self.metadata_form["extra_fields"]["Arc Path"]["value"] = arc_path
        
        if data.startswith("weighing_mgram"):
            weighing_order = self.metadata_form["extra_fields"]["Weighing Order"]["value"]
            if weighing_order == " ":
                weighing_order = data.split("_")[2]
            else:
                weighing_order = f"{weighing_order}, {data.split('_')[2]}"
            self.metadata_form["extra_fields"]["Weighing Order"]["value"] = weighing_order

            target_quantity = self.metadata_form["extra_fields"]["Target Quantity"]["value"]
            if target_quantity == " ":
                target_quantity = data.split("_")[3]
            else:
                quantity = data.split("_")[3]
                target = round((int(target_quantity) + int(quantity)), 3)
            self.metadata_form["extra_fields"]["Target Quantity"]["value"] = str(target)
        
        if data.startswith("plc_autoFlip"):
            number_of_flips = self.metadata_form["extra_fields"]["Number of Flips"]["value"]
            if number_of_flips == " ":
                number_of_flips = 1
            else:
                number_of_flips = int(number_of_flips) + 1
            self.metadata_form["extra_fields"]["Number of Flips"]["value"] = str(number_of_flips)
        
        if "Weight:" in data:
            match = re.search(r"Weight:\s*([-+]?[0-9]*\.?[0-9]+)", data)
            if match:
                total_mass_after_arc = match.group(1)
                self.metadata_form["extra_fields"]["Total Mass After Arc"]["value"] = str(total_mass_after_arc)

        
        

    def update_metadata(self):
        self.metadata_form["extra_fields"]["number"]["value"] = self.experiment_id
        payload = {"metadata": json.dumps(self.metadata_form)}
        patch_resp = requests.patch(
            f"{self.api_url}/experiments/{self.experiment_id}", 
            headers=self.headers,
            data=json.dumps(payload), 
            verify=False)
        if patch_resp.status_code == 200:
            print("Metadata uploaded")
        else:
            print("Failed to upload metadata:", patch_resp.status_code, patch_resp.text)

test = False

if test:
    # Example usage
    elabdb = ElabFTW(BASE_URL, API_KEY)
    expriment_id = elabdb.create_experiment("test123")
    elabdb.update_form("Arc Path","777")
    elabdb.update_metadata()
    
