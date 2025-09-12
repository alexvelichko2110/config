#ifndef _VALUE_H_
#define _VALUE_H_

#include <string>

class Value
{
    public:

        Value()
        {

        }

        Value(float val, float min, float max, float step)
        {
            _type = "float";
            _float_val = val;
            _float_min = min;
            _float_max = max;
            _float_step = step;
        }

        Value(int val, int min, int max, int step)
        {
            _type = "int";
            _int_val = val;
            _int_min = min;
            _int_max = max;
            _int_step = step;
        }

        Value(const std::string &str)
        {
            _type = "str";
            _str_val = str;
        }

        void forward()
        {

            if (_type == "float") {
                if (_float_val < _float_max)
                    _float_val += _float_step;
            } else if (_type == "int") {
                if (_int_val < _int_max)
                    _int_val += _int_step;
            }
        }

        void back()
        {
            if (_type == "float") {
                if (_float_val < _float_max)
                    _float_val += _float_step;
            } else if (_type == "int") {
                if (_int_val > _int_min)
                    _int_val -= _int_step;
            }
        }

        float as_float()
        {
            return _float_val;
        }

        int as_int()
        {
            return _int_val;
        }

        std::string as_str()
        {
            return _str_val;
        }

        std::string get_type()
        {
            return _type;
        }

        int get_int_max() {
            return _int_max;
        }

        int get_int_min() {
            return _int_min;
        }

        int get_int_step() {
            return _int_step;
        }

        
        int get_float_max() {
            return _float_max;
        }

        int get_float_min() {
            return _float_min;
        }

        int get_float_step() {
            return _float_step;
        }

    private:

        std::string _type;

        float _float_val;
        int _float_min = 0;
        int _float_max = 0;
        int _float_step = 0;

        int _int_val;
        int _int_min = 0;
        int _int_max = 0;
        int _int_step = 0;

        std::string _str_val;
};

#endif // _VALUE_H_
