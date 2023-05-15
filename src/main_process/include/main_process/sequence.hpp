#include <chrono>
#include <cstdlib>
#include <memory>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <vector>

#include <iostream>

class SequenceState {
public:
    virtual void process() = 0;
};

class init : public SequenceState {
public:
    void process();
};

class outDosingHead : public SequenceState {
public:
    void process();
};

class inDosingHead : public SequenceState {
public:
    void process();
};

class outWeighingSample : public SequenceState {
public:
    void process();
};

class inWeighingSample : public SequenceState {
public:
    void process();
};

class outBufferSample : public SequenceState {
public:
    void process();
};

class inBufferSample : public SequenceState {
public:
    void process();
};

class weighing : public SequenceState {
public:
    void process();
};


class Sequence {
private:
    SequenceState* state;

public:
    Sequence() {
        state = new init();
    }

    void setState(SequenceState* newState) {
        delete state;
        state = newState;
    }

    void process() {
        state->process();
    }
};