import os
from datetime import datetime
import requests
import json

class ElabFTW:
    def __init__(self, api_url, api_key):
        self.api_url = api_url
        self.headers = {
            "Authorization": f"Bearer {api_key}",
            "Content-Type": "application/json"
        }
        self.experiment_id = None
        self.session_start_time = datetime.now()
    
    def create_experiment(self, title, body="", category_id=1):
        """創建新實驗"""
        payload = {
            "title": title,
            "body": body,
            "category_id": category_id,
            "date": datetime.now().strftime('%Y-%m-%d')
        }
        
        response = requests.post(
            f"{self.api_url}/experiments",
            headers=self.headers,
            data=json.dumps(payload)
        )
        
        if response.status_code == 201:
            self.experiment_id = response.json().get("id")
            return self.experiment_id
        else:
            return None
    
    def add_data(self, data, description=""):
        """添加實驗數據"""
        timestamp = datetime.now().strftime('%Y-%m-%d %H:%M:%S')
        formatted_data = f"{timestamp} - {description}: {data}"
        
        if self.experiment_id:
            # get from elabftw
            response = requests.get(
                f"{self.api_url}/experiments/{self.experiment_id}",
                headers=self.headers
            )
            
            if response.status_code == 200:
                current_content = response.json().get("body", "")
                new_content = f"{current_content}\n\n{formatted_data}"
                
                # update
                update_payload = {"body": new_content}
                update_response = requests.patch(
                    f"{self.api_url}/experiments/{self.experiment_id}",
                    headers=self.headers,
                    data=json.dumps(update_payload)
                )