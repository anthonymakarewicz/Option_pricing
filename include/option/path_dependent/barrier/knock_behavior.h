#ifndef KNOCK_BEHAVIOR_H
#define KNOCK_BEHAVIOR_H

namespace OptionPricer {
    class KnockBehavior {
    public:
        virtual ~KnockBehavior();
        [[nodiscard]] virtual bool isActive(bool barrierBreached) const = 0;
    };

    class KnockIn : public KnockBehavior {
    public:
        ~KnockIn() override;
        [[nodiscard]] bool isActive(bool barrierBreached) const override;
    };

    class KnockOut : public KnockBehavior {
    public:
        ~KnockOut() override;
        [[nodiscard]] bool isActive(bool barrierBreached) const override;
    };
}

#endif //KNOCK_BEHAVIOR_H