#ifndef KNOCK_BEHAVIOR_CPP
#define KNOCK_BEHAVIOR_CPP

class KnockBehavior {
public:
    virtual bool isActive(bool barrierBreached) const = 0;
    virtual ~KnockBehavior() = default;
};

class KnockIn : public KnockBehavior {
public:
    bool isActive(bool barrierBreached) const override {
        return barrierBreached;
    }
};

class KnockOut : public KnockBehavior {
public:
    bool isActive(bool barrierBreached) const override {
        return !barrierBreached;
    }
};

#endif //KNOCK_BEHAVIOR_CPP
