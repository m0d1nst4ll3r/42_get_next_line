# 42_get_next_line

Just finished.

ez

Todo:

- Check with peers?
- Redo it without a shitty realloc so that I can parse big lines in less than 2 hours
	- The idea is to realloc only once I've gotten either to the end of the buffer, or to the next newline
	- This way a 1000-char line would realloc 1000/BUFFER_SIZE times maximum, not 1000 times
	- But it's annoying to make. Kinda. If it ain't broken don't fix it. (who has files with 1000-char lines)
