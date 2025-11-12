#include "include/correlation.h"

bool auto_correlation(uint16_t data_size, int8_t *data, int8_t *output)
{
    if (data_size < RANGE || data_size < 50)
        return false;
    if (!data || !output)
        return false;

    int16_t sumsq = 0;

    bool new_lap = false;

    uint16_t i = 0;
    for (; i < data_size; ++i) 
    {
        sumsq += data[i] * data[i];
    }
    

    i = data_size - RANGE;
    uint16_t k = 0;
    for (; i < data_size; ++i) 
    {
        int16_t sumprod = 0;

        uint16_t j = 0;
        for (; j < (data_size - i); ++j) 
        {
            sumprod = sumprod + (data[j] * data[j+i]);
        }

        int16_t num = SCALE * data_size * sumprod;
        int16_t den = (data_size - i) * sumsq;

        output[k] = num/den;

        if (output[k] > TRESHOLD)
        {
            new_lap = true;
            //return new_lap;
        }

        k++;
    }

    return new_lap;
}