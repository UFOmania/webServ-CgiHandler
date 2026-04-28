#!/usr/bin/env python3
import os
import json

def main():
	body = input()
	print("body : {" + body + "}");
	allowed_keys = [
		"REQUEST_METHOD",
		"QUERY_STRING",
		"SCRIPT_NAME"
	]
	env = {key: os.environ[key] for key in allowed_keys if key in os.environ}
	print(json.dumps(env, indent=2))

if __name__ == "__main__":
	main()

