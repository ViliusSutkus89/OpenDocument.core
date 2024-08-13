#!/usr/bin/env python3
import argparse
import json
import os
import sys


def main():
    parser = argparse.ArgumentParser(description="Get path to installed odrcore from json, generated by conan create")
    parser.add_argument("--version", nargs='?', help="Which version of odrcore to look for, defaults to 0.0.0")
    parser.add_argument("json_from_conan_create")
    args = parser.parse_args()
    del parser

    version = args.version if args.version is not None else "0.0.0"
    with open(args.json_from_conan_create, 'r') as f:
        for node in json.load(f)['graph']['nodes'].values():
            if node['ref'].startswith(f"odrcore/{version}"):
                package_folder = node['package_folder']
                print(package_folder)

                gh_output = os.environ.get('GITHUB_OUTPUT')
                if gh_output:
                    with open(gh_output, 'w') as out:
                        print(f"package_folder={package_folder}")

                sys.exit(0)
    sys.exit(1)


if __name__ == "__main__":
    main()
