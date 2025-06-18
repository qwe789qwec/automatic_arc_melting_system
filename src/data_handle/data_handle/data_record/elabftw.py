from datetime import datetime
import requests
import json
import os

# and this one to pretty print python object
from pprint import pprint

import elabapi_python
import urllib3

class ElabFTW:
    def __init__(self, api_url, api_key):
        # Set the API URL
        self.api_url = api_url
        # Set the API key
        self.api_key = api_key
        
        # Initialize a configuration object from the library
        self.configuration = elabapi_python.Configuration()
        self.configuration.host = self.api_url
        self.configuration.verify_ssl = False
        self.configuration.debug = False
        
        # Disable SSL warnings if verification is disabled
        if not self.configuration.verify_ssl:
            urllib3.disable_warnings(category=urllib3.exceptions.InsecureRequestWarning)
        
        # Create API client and set authorization header
        self.api_client = elabapi_python.ApiClient(self.configuration)
        self.api_client.set_default_header(header_name='Authorization', header_value=self.api_key)
        
        # Initialize API endpoints
        self.info_client = elabapi_python.InfoApi(self.api_client)
        self.exp_client = elabapi_python.ExperimentsApi(self.api_client)
        self.items_client = elabapi_python.ItemsApi(self.api_client)

    def get_instance_info(self):
        return self.info_client.get_info()

    def create_experiment(self, title=None, body=None, tags=None):
        exp_data = {
            "title": title,
            "body": body,
            "tags": tags
        }
        
        response_data, status_code, headers = self.exp_client.post_experiment_with_http_info(
            body=exp_data if exp_data else None
        )
        
        location = headers.get('Location')
        exp_id = int(location.split('/').pop())
        
        if status_code == 201:
            experiment = self.exp_client.get_experiment(exp_id)
            return exp_id, experiment
        else:
            raise Exception(f"Failed to create experiment. Status code: {status_code}")

    def get_experiment(self, experiment_id):
        return self.exp_client.get_experiment(experiment_id)

    def update_experiment(self, experiment_id, data):
        return self.exp_client.patch_experiment(experiment_id, body=data)

    def create_item(self, category_id, title=None, body=None, tags=None):
        item_data = {"category_id": category_id}
        if title:
            item_data["title"] = title
        if body:
            item_data["body"] = body
        if tags:
            item_data["tags"] = tags
        
        response_data, status_code, headers = self.items_client.post_item_with_http_info(body=item_data)
        
        location = headers.get('Location')
        item_id = int(location.split('/').pop())
        
        if status_code == 201:
            item = self.items_client.get_item(item_id)
            return item_id, item
        else:
            raise Exception(f"Failed to create item. Status code: {status_code}")

    def get_item(self, item_id):
        return self.items_client.get_item(item_id)

    def update_item(self, item_id, data):
        return self.items_client.patch_item(item_id, body=data)
    
    def finalize_experiment(self, experiment_id):
        # Assuming there's a status field that can be set to indicate completion
        # You may need to adapt this based on how ElabFTW actually handles experiment completion
        return self.update_experiment(experiment_id, {"status": "finished"})
    
    def delete_experiment(self, experiment_id):
        response_data, status_code, headers = self.exp_client.delete_experiment_with_http_info(experiment_id)
        return status_code == 204

    def delete_item(self, item_id):
        response_data, status_code, headers = self.items_client.delete_item_with_http_info(item_id)
        return status_code == 204

test = True

if test:
    # Example usage
    elab = ElabFTW(
    )

    info = elab.get_instance_info()
    print(f"Connected to ElabFTW instance with {info.teams_count} teams and {info.all_users_count} users.")
    
    # Create a new experiment
    exp_id, experiment = elab.create_experiment(
        title="Testing the ElabFTW class",
        body="<p>This is a test experiment created using the ElabFTW class.</p>",
        tags=["test", "api", "python"]
    )
    print(f"Created experiment #{exp_id}: {experiment.title}")
    
    # Add data (item) - you'll need to know the category_id for your instance
    category_id = 1  # Replace with an actual category ID from your ElabFTW instance
    item_id, item = elab.create_item(
        category_id=category_id,
        title="Test data entry",
        body="<p>This is test data associated with the experiment.</p>",
        tags=["data", "test"]
    )
    print(f"Created data item #{item_id}: {item.title}")
    
    # Update the data
    updated_item = elab.update_item(item_id, {
        "title": "Updated test data entry",
        "body": "<p>This data has been updated.</p>"
    })
    print(f"Updated data item: {updated_item.title}")
    
    # Finalize the experiment
    finalized = elab.finalize_experiment(exp_id)
    print(f"Experiment finalized: {finalized.status}")
    
    print(f"You can view the experiment at: {experiment.sharelink}")