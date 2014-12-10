import os
import sys

HEADER_EXTENSION = ".hpp"
SOURCE_EXTENSION = ".cpp"
HEADER_FOLDER = "header"
SOURCE_FOLDER = "src"

if len(sys.argv) < 2:
    print("you dead")
    sys.exit(-1)
else:
    name = sys.argv[1]

parts = name.split("/")
class_name = parts[-1]

header_folder = os.path.join(HEADER_FOLDER, *parts[:-1])
source_folder = os.path.join(SOURCE_FOLDER, *parts[:-1])
header_path = os.path.join(header_folder, class_name + HEADER_EXTENSION)
source_path = os.path.join(source_folder, class_name + SOURCE_EXTENSION)

# Create header
if not os.path.isdir(header_folder):
    os.makedirs(header_folder)

if not os.path.isfile(header_path):
    print("Creating %s" % header_path)
    with open(header_path, "w") as f:
        guard = class_name.upper() + HEADER_EXTENSION.replace(".", "_").upper()
        f.write('#ifndef %s\n' % guard)
        f.write('#define %s\n\n' % guard)
        f.write('class %s {\n\n};\n\n' % class_name)
        f.write('#endif\n')

# Create source
if not os.path.isdir(source_folder):
    os.makedirs(source_folder)

if not os.path.isfile(source_path):
    print("Creating %s" % source_path)
    with open(source_path, "w") as f:
        f.write('#include "%s"\n' % (name + HEADER_EXTENSION))
