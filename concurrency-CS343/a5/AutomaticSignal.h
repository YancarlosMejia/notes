#ifndef AUTOMATICSIGNAL_H
#define AUTOMATICSIGNAL_H

#define AUTOMATIC_SIGNAL \
    uCondition cond

#define WAITUNTIL(pred, before, after) \
    if (!(pred)) { \
        before; \
        while (!cond.empty()) { cond.signal(); } \
        while (!(pred)) { \
            cond.wait(); \
        } \
        after; \
    }

#define RETURN(expr...) \
    while (!cond.empty()) { cond.signal(); } \
    return (expr)

#endif
