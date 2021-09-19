#!/usr/bin/env python2
ctxt = '"sokk mjsbvuok" rm u qubbko js frtkobi, gjb norwk. bj xgpkombugp bhk wjgwknb, ijx mhjxfp bhrgl js "sokk" um rg "sokk mnkkwh," gjb um rg "sokk tkko."'
values = list(ctxt)

histogram = lambda s: (lambda d: [[d.__setitem__(c, d.get(c, 0)+1) for c in s], d][-1])(dict())
prettyhist = lambda h: [__import__('sys').stdout.write('%c: %s\n' % (k, '*'*v)) for (k, v) in sorted(h.items(), key=lambda (x,y): y, reverse=True)][-1]

while True:
    print('Current ciphertext: %r' % (''.join(values),))
    prettyhist(histogram(values))
    xs = raw_input('pair of letters to swap> ').split(' ')
    if len(xs) == 2 and len(xs[0]) == 1 and len(xs[1]) == 1:
        for i in range(len(values)):
            values[i] = {xs[0]: xs[1], xs[1]: xs[0]}.get(values[i], values[i])
