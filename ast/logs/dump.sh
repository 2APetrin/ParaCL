#!/bin/bash

gr="/graphviz/"
gr_name="graphviz"
gr_p=".dot"
im="/images/"
im_name="tree_dump"
im_nm_p=".png"

dot $1${gr}${gr_name}$2${gr_p} -Tpng -o $1${im}${im_name}$2${im_nm_p}