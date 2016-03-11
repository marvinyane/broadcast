#include <memory>

class BroadMessage;

class BroadSignal
{
    public:
        BroadSignal();
        virtual ~BroadSignal();
        int broadcast(std::shared_ptr<BroadMessage> message);

    private:
        BroadSignal(const BroadSignal&);
        BroadSignal& operator=(const BroadSignal&);

    private:
        struct Private;
        Private *pri;

};
