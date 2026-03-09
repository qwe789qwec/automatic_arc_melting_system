#!/usr/bin/env python3
import os
import json
import pandas as pd
import rclpy
from rclpy.node import Node
from msg_format.msg import ProcessMsg
from threading import Lock

class TaskManager(Node):
    def __init__(self):
        super().__init__('task_manager')
        
        # CSVの既定パスを src/sequence/task.csv に
        default_csv_path = os.path.abspath(
            os.path.join(os.getcwd(), 'sequence', 'task.csv')
        )
        self.declare_parameter('csv_path', default_csv_path)
        self.csv_path = self.get_parameter('csv_path').get_parameter_value().string_value
        
        # 発行: new_task（タスク情報をJSONで）
        self.pub_new_task = self.create_publisher(ProcessMsg, 'new_task', 10)
        
        # 購読: task_status（完了/失敗通知を受けてCSV更新）
        self.sub_task_status = self.create_subscription(
            ProcessMsg, 'task_status', self.on_task_status, 10
        )
        
        # 実行中タスクの排他制御
        self.current_task_id = None
        self.lock = Lock()
        
        # 周期チェック（3秒ごと）
        self.timer = self.create_timer(3.0, self.tick)
        self.get_logger().info(f'TaskManager started. csv_path={self.csv_path}')
    
    def tick(self):
        """CSVを定期的にチェックして新しいタスクを処理"""
        with self.lock:
            # すでに処理中のタスクがあればスキップ
            if self.current_task_id is not None:
                return
            
            # CSV読み込み
            try:
                df = pd.read_csv(self.csv_path)
            except Exception as e:
                self.get_logger().error(f'CSV read error: {e}')
                return
            
            # status列の確認
            if 'status' not in df.columns:
                self.get_logger().error('CSV missing "status" column')
                return
            
            # to_be_done のタスクを検索
            pending = df[df['status'] == 'to_be_done']
            if pending.empty:
                return
            
            # 先頭のタスクを取得
            task = pending.iloc[0]
            
            # task_id の取得（列があればそれを、なければindexを使用）
            if 'task_id' in df.columns:
                task_id = int(task['task_id'])
            else:
                task_id = int(task.name)
            
            # CSVのstatusを processing に更新
            df.loc[task.name, 'status'] = 'processing'
            try:
                df.to_csv(self.csv_path, index=False)
            except Exception as e:
                self.get_logger().error(f'CSV write error (processing): {e}')
                return
            
            # タスク情報をJSONに変換
            payload = task.to_dict()
            payload['task_id'] = task_id
            
            # ProcessMsg にJSONを格納してpublish
            msg = ProcessMsg()
            msg.process = json.dumps(payload, ensure_ascii=False)
            self.pub_new_task.publish(msg)
            
            # 現在のタスクIDを記録
            self.current_task_id = task_id
            self.get_logger().info(f'Published new_task: task_id={task_id}')
    
    def on_task_status(self, msg: ProcessMsg):
        """タスク完了/失敗通知を受信してCSVを更新"""
        text = msg.process.strip()
        
        # メッセージ形式の解析
        if text.startswith('TASK_COMPLETED='):
            new_status = 'completed'
            task_id = int(text.split('=')[1])
        elif text.startswith('TASK_FAILED='):
            new_status = 'failed'
            task_id = int(text.split('=')[1])
        else:
            # 関係ないメッセージは無視
            return
        
        with self.lock:
            # CSV読み込み
            try:
                df = pd.read_csv(self.csv_path)
            except Exception as e:
                self.get_logger().error(f'CSV read error (status update): {e}')
                return
            
            # 該当タスクを検索
            if 'task_id' in df.columns:
                # task_id列で照合
                try:
                    mask = (df['task_id'].astype(int) == task_id)
                except Exception:
                    mask = (df['task_id'] == task_id)
            else:
                # indexで照合
                try:
                    mask = (df.index.astype(int) == task_id)
                except Exception:
                    mask = (df.index == task_id)
            
            # ステータス更新
            if hasattr(mask, 'any') and mask.any():
                df.loc[mask, 'status'] = new_status
                try:
                    df.to_csv(self.csv_path, index=False)
                    self.get_logger().info(f'Updated task_id={task_id} -> {new_status}')
                except Exception as e:
                    self.get_logger().error(f'CSV write error ({new_status}): {e}')
            else:
                self.get_logger().warn(f'task_id={task_id} not found in CSV')
            
            # 次のタスクを処理できるようにクリア
            self.current_task_id = None
            
def main(args=None):
    rclpy.init(args=args)
    node = TaskManager()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()