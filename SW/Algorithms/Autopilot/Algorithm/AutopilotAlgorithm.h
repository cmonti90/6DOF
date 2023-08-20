#ifndef AutopilotAlgorithm_H
#define AutopilotAlgorithm_H

class AutopilotAlgorithm
{
public:
    AutopilotAlgorithm();
    virtual ~AutopilotAlgorithm();

    void initialize();
    void process();
    void finalize();

private:

};

#endif /* AutopilotAlgorithm_H */
