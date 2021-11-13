#!/bin/bash

MY_DIR=$(cd `dirname $0` && pwd)

exec qemu-system-x86_64 -m 2G \
    -net nic,model=ne2k_pci -net user \
    -hda $MY_DIR/reactos.vmdk -cdrom $MY_DIR/bootcd.iso \
    -boot d -serial stdio
