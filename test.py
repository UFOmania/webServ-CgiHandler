#!/usr/bin/env python3
import os
import json

def main():
	body = input()
	print("body : {" + body + "}");
	allowed_keys = [
		"REQUEST_METHOD",
		"QUERY_STRING",
		"SCRIPT_NAME",
		"CONTENT_LENGTH",
		"CONTENT_TYPE",
		"GATEWAY_INTERFACE",
		"SERVER_PROTOCOL",
		"SERVER_SOFTWARE",
		"SERVER_NAME",
		"SERVER_PORT",
		"REMOTE_ADDR",
		"HTTP_ACCEPT",
		"HTTP_AUTHORIZATION",
		"HTTP_CONNECTION",
		"HTTP_CONTENT_ENCODING",
		"HTTP_CONTENT_LENGTH",
		"HTTP_CONTENT_TYPE",
		"HTTP_DATE",
		"HTTP_FROM",
		"HTTP_IF_MODIFIED_SINCE",
		"HTTP_PRAGMA",
		"HTTP_REFERER",
		"HTTP_USER_AGENT",
	]
	env = {key: os.environ[key] for key in allowed_keys if key in os.environ}
	print(json.dumps(env, indent=2))

if __name__ == "__main__":
	main()

