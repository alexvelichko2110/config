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
            float val = 0.0f;

            if (_type == "float")
                val = _float_val;
            else if (_type == "int")
                val = _int_val;
            else if (_type == "str")
                val = std::atof(_str_val.c_str());

            return val;
        }

        int as_int()
        {
            int val = 0;

            if (_type == "int")
                val = _int_val;
            else if (_type == "float")
                val = _float_val;
            else if (_type == "str")
                val = std::atoi(_str_val.c_str());

            return val;
        }

        std::string as_str()
        {
            std::string val = " ";

            if (_type == "int")
                val = std::to_string(_int_val);
            else if (_type == "float")
                val = std::to_string(_float_val);
            else if (_type == "str")
                val = _str_val;

            return val;
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
