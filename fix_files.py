import os
import sys

if len(sys.argv) < 2:
    dir = '.'
else:
    dir = sys.argv[1]

sources="src"
out="target"
headers="header"

for root, dirs, files in os.walk(os.path.join(dir, headers), topdown=True):
    # Copying folder structure
    for dirname in dirs:
        in_src_folder = os.path.join(root.replace(headers, sources), dirname)
        in_out_folder = os.path.join(root.replace(headers, out), dirname)

        if not os.path.isdir(in_src_folder):
            print("Creating %s folder..." % in_src_folder)
            os.makedirs(in_src_folder)

        if not os.path.isdir(in_out_folder):
            print("Creating %s folder..." % in_out_folder)
            os.makedirs(in_out_folder)

    # Creating cpp files including their own header
    for name in files:
        if not name.endswith(".hpp"):
            continue

        in_src_file = os.path.join(root.replace(headers, sources), name.replace(".hpp", ".cpp"))

        if not os.path.isfile(in_src_file):
            to_include = os.path.join(root.replace(os.path.join(dir, headers), ""), name).replace("\\", "/").strip("/")
            print("Creating %s file..." % in_src_file)
            with open(in_src_file, "w") as f:
                f.write('#include "%s"\n' % to_include)
