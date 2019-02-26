#ifndef SCREEN_H
#define SCREEN_H

enum roastStates {
    STOPPED = 0,
    DRY,
    FC,
    FCE,
    SC,
    DROP,
    MAILL,
    FIN,
};

class Screen {
    private:
        virtual void doRefresh(void) = 0;
    protected:
        bool wifiEnabled = false;
        double ET, BT, SP, ROR = 0;
        unsigned int fanDutyCycle, RINT = 0;
        unsigned long roastDuration = 0;
        roastStates roastStatus = STOPPED;
        bool isCelsius = true;
    public:
        virtual ~Screen() {};
        void setRoastStatus(roastStates status);
        void useCelsius(void);
        void useFarhenheit(void);
        void setWIFIStatus(bool enabled);
        void setET(double temp);
        void setBT(double temp);
        void setSP(double temp);
        void setFan(unsigned int dutyCycle);
        void setROR(double ror);
        void setRINT(unsigned int rorInterval);
        void setDuration(unsigned long duration);
        void refresh(void);
};

#endif
