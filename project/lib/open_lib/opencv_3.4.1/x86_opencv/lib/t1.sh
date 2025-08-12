#! /bin/bash
for file in *.so.3.4.1; do
	base_name="${file%.3.4.1}"
	ln -sfv "$file" "$base_name"
done
