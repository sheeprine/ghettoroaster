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

#include "ror_calculator.h"

RORCalculator::RORCalculator(unsigned int samplingInterval, unsigned int historySize) : m_samplingInterval(samplingInterval) {
    m_sampleNum = historySize/m_samplingInterval;
    m_history.reserve(m_sampleNum);
}

double RORCalculator::get(unsigned int interval) {
    div_t samples = div(interval, m_samplingInterval);
    double scale = static_cast<double>(samples.rem)/m_samplingInterval;
    return getSum(samples.quot, scale);
}

double RORCalculator::get() {
    if (m_history.empty())
        return -1;
    return m_history.back();
}

double RORCalculator::getSum(unsigned int numSamples, double scaleLast) {
    if (numSamples > m_sampleNum)
        return -1;
    if (numSamples > m_history.size()) {
        numSamples = m_history.size();
        scaleLast = 0;
    }
    double sum = 0.0;
    auto it = m_history.rbegin();
    for ( ; it != m_history.rbegin() + numSamples; ++it)
        sum += *it;
    if (scaleLast)
        sum += *it * scaleLast;
    return sum;
}

void RORCalculator::update(double value) {
    m_history.push_back(value - m_lastTemp);
    m_lastTemp = value;
    if (m_history.size() > m_sampleNum)
        m_history.erase(m_history.begin());
}

void RORCalculator::reset() {
    m_history.clear();
}
