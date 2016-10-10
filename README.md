Purpose
=======
Evaluate the effects of prefetching.
Reference matrix transpose results on Intel Core(TM) i5-3320M CPU @ 2.60GHz:
```
sse prefetch:     55554 us
sse:             113594 us
naive:           222115 us
```

The work was based on the experiments by `Champ Yen <champ.yen@gmail.com>`.

Coding Style
============
You can use [AStyle](http://astyle.sourceforge.net/) source code indenter to
help you auto format your source code. It will for sure not correct all your coding styles but for sure will eliminate most of them.

To format your file you can execute below command:
```sh
astyle --style=kr --indent=spaces=4 --indent-switches --suffix=none *.[ch]
```
