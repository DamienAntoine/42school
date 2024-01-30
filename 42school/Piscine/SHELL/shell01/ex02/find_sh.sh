#/bin/bash

find . -type f -name '*.sh' |

while read -r file; do

echo "$(basename "$file" .sh)"
done
