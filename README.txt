# 42_get_next_line

Version 2 with better realloc, cuts down time tremendously on huge lines.
(only if BUFFER_SIZE is big enough)

Todo:

- Check with peers?

- Improve on time with huge lines when BUFFER_SIZE = 1 by using a chained list of chars instead of reallocing every byte. This way you avoid having to copy 9k+ bytes 1k times on 10k lines with a single byte buffer

- Tester: git@github.com:Tripouille/gnlTester.git
