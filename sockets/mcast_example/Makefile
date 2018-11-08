SRC1=mcastRecvSrc
SRC2=mcastSendSrc

default: all

all:
	@cd $(SRC1) && make
	@cd $(SRC2) && make

clean:
	@cd $(SRC1) && make clean
	@rm -rf *~
	@cd $(SRC2) && make clean
	@rm -rf *~

distclean: clean
	@cd $(SRC1) && make distclean
	@cd $(SRC2) && make distclean

.PHONY: all clean distclean
