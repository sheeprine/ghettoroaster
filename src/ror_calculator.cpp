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

RORCalculator::RORCalculator(unsigned int samplingInterval, unsigned int historySize) : m_RORSamplingInterval(samplingInterval) {
    m_RORSampleNum = historySize/m_RORSamplingInterval;
    m_RORHistory.reserve(m_RORSampleNum);
}

double RORCalculator::getROR(unsigned int interval) {
    div_t samples = div(interval, m_RORSamplingInterval);
    double scale = static_cast<double>(samples.rem)/m_RORSamplingInterval;
    return getRORSum(samples.quot, scale);
}

double RORCalculator::getROR() {
    if (m_RORHistory.empty())
        return -1;
    return m_RORHistory.back();
}

double RORCalculator::getRORSum(unsigned int num_samples, double scale_last) {
    if (num_samples > m_RORSampleNum)
        return -1;
    if (num_samples > m_RORHistory.size()) {
        num_samples = m_RORHistory.size();
        scale_last = 0;
    }
    double sum = 0.0;
    auto it = m_RORHistory.rbegin();
    for ( ; it != m_RORHistory.rbegin()+num_samples; ++it)
        sum += *it;
    if (scale_last)
        sum += *it * scale_last;
    return sum;
}

void RORCalculator::updateROR(double value) {
    m_RORHistory.push_back(value - m_lastTemp);
    m_lastTemp = value;
    if (m_RORHistory.size() > m_RORSampleNum)
        m_RORHistory.erase(m_RORHistory.begin());
}

void RORCalculator::resetROR() {
    m_RORHistory.clear();
}
