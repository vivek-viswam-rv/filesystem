# A simple filesystem

An *N-array tree* based filesystem, with all the files and folders in the same directory level represented in the same level of the filesystem tree.

The filesystem could be implemented as custom filesystem using loadable Linux kernel module for Linux based systems.

## Supported operations

The filesystem supports the following operations

| Operation | Description |
|:---|:---|
| Insert | Create a new file/folder |
| Search | Seach for an existing file/folder |
| Delete | Delete an existing file/folder |
| Display | Print all existing files/folders in the filesystem |

## Working

1. Create an executable from the file [filesystem.c](filesystem.c) using `gcc`
2. On executing the generated executable, the user is presented with a menu to choose one of the [Supported operations](#Supported-operations)
3. The user is asked for various details such as parent directory as per the requirement of the operation selected
4. On completing the operation, the user is taken back to the main menu
