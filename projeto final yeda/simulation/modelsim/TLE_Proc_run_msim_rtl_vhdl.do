transcript on
if {[file exists rtl_work]} {
	vdel -lib rtl_work -all
}
vlib rtl_work
vmap work rtl_work

vcom -93 -work work {C:/Users/Aluno/Desktop/caio/projeto final yeda/nanoProc.vhd}
vcom -93 -work work {C:/Users/Aluno/Desktop/caio/projeto final yeda/DMEMORY.VHD}

