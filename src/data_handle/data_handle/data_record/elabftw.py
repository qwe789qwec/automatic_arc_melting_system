import os
from datetime import datetime
import requests
import json

class ElabFTW:
    def __init__(self, api_url, api_key, local_backup=True, backup_dir="experiment_logs"):
        self.api_url = api_url
        self.headers = {
            "Authorization": f"Bearer {api_key}",
            "Content-Type": "application/json"
        }
        self.experiment_id = None
        self.session_start_time = datetime.now()
        
        # 本地備份設置
        self.local_backup = local_backup
        if local_backup:
            self.backup_dir = backup_dir
            os.makedirs(self.backup_dir, exist_ok=True)
            self.backup_file = os.path.join(
                self.backup_dir, 
                f"experiment_{datetime.now().strftime('%Y-%m-%d')}.txt"
            )
    
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
            self._log_local(f"創建實驗: {title} (ID: {self.experiment_id})")
            return self.experiment_id
        else:
            self._log_local(f"創建實驗失敗: {response.text}")
            return None
    
    def add_data(self, data, description=""):
        """添加實驗數據"""
        timestamp = datetime.now().strftime('%Y-%m-%d %H:%M:%S')
        formatted_data = f"{timestamp} - {description}: {data}"
        
        if self.experiment_id:
            # 從elabFTW獲取當前內容
            response = requests.get(
                f"{self.api_url}/experiments/{self.experiment_id}",
                headers=self.headers
            )
            
            if response.status_code == 200:
                current_content = response.json().get("body", "")
                new_content = f"{current_content}\n\n{formatted_data}"
                
                # 更新實驗內容
                update_payload = {"body": new_content}
                update_response = requests.patch(
                    f"{self.api_url}/experiments/{self.experiment_id}",
                    headers=self.headers,
                    data=json.dumps(update_payload)
                )
                
                if update_response.status_code == 200:
                    self._log_local(f"數據已添加: {formatted_data}")
                else:
                    self._log_local(f"數據添加失敗: {update_response.text}")
            else:
                self._log_local(f"獲取實驗內容失敗: {response.text}")
        else:
            self._log_local(f"未創建實驗，僅本地記錄: {formatted_data}")
        
        # 無論API成功與否，都本地記錄
        self._log_local(formatted_data)
    
    def _log_local(self, message):
        """記錄到本地文件"""
        if self.local_backup:
            timestamp = datetime.now().strftime('%Y-%m-%d %H:%M:%S')
            with open(self.backup_file, 'a', encoding='utf-8') as f:
                f.write(f"{timestamp} - {message}\n")
    
    def __del__(self):
        """析構函數，記錄會話結束"""
        if hasattr(self, 'local_backup') and self.local_backup:
            session_duration = datetime.now() - self.session_start_time
            self._log_local(f"實驗記錄會話結束，持續時間: {session_duration}")