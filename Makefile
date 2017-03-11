CFLAGS = -msse2 --std gnu99 -O0 -Wall -Wextra

GIT_HOOKS := .git/hooks/applied

all: $(GIT_HOOKS) main.c
	$(CC) $(CFLAGS) -o main main.c

$(GIT_HOOKS):
	@scripts/install-git-hooks
	@echo

clean:
	$(RM) main
