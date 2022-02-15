all:
	$(MAKE) -C Stellar
	$(MAKE) -C Sandbox

run:
	$(MAKE) -C Sandbox run

clean:
	$(MAKE) -C Stellar clean
	$(MAKE) -C Sandbox clean