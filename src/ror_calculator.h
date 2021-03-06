/*
Copyright 2019 Stephane Albert

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

   http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#ifndef ROR_CALCULATOR_H
#define ROR_CALCULATOR_H

#include <cmath>
#include <cstdlib>
#include <vector>

#define ROR_HISTORY_SIZE 30

class RORCalculator {
    public:
        RORCalculator(unsigned int samplingInterval,
            unsigned int historySize=ROR_HISTORY_SIZE);
        double get();
        double get(unsigned int interval);
        void update(double value);
        void reset();

    private:
        unsigned int m_samplingInterval;
        unsigned int m_sampleNum = 0;
        double m_lastTemp = 0;
        std::vector<double> m_history;
        double getSum(unsigned int numSamples, double scaleLast=0.0);
};

#endif
