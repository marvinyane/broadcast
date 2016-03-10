#include <memory>

class BroadMessage;

class BroadSignal
{
    public:
        BroadSignal(std::shared_ptr<BroadMessage> message);
        virtual ~BroadSignal();
        int broadcast();

    private:
        BroadSignal();
        BroadSignal(const BroadSignal&);
        BroadSignal& operator=(const BroadSignal&);

    private:
        std::shared_ptr<BroadMessage> message;

        struct Private;
        Private *pri;

};
