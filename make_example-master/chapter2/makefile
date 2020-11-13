#this makefile is test for include process
.PHONY:all clean
include ./makefile_dir/inc_a ./makefile_dir/inc_b
vari_a += " 2nd vari..."
all:
	@echo $(vari_a)
	@echo $(MAKEFILE_LIST)
clean: