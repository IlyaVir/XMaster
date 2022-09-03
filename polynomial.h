#include <iostream>
#include <algorithm>
#include <cmath>
#include <stack>
#include <fstream>
#include <vector>

struct polynomial {
    long long coefficient, power;
    polynomial *next;
};

struct list_solves {
    long long solve;
    list_solves *next;
};

struct error {
    long long code, pos;
    std::string text;
};

void throw_error(int code, std::string text) {
    std::pair <int, std::string> error;
    error.first = code;
    error.second = text;
    throw(error);
}

void throw_error(int code, std::string text, int pos) {
    error err;
    err.code = code;
    err.text = text;
    err.pos = pos;
    throw(err);
}

polynomial *number_to_polynomial(long long number) {
    polynomial *helper;
    if (number == 0) {
        helper = nullptr;
    } else {
        helper = new polynomial;
        helper -> next = nullptr;
        helper -> coefficient = number;
        helper -> power = 0;
    }
    return helper;
}

polynomial *create_x(long long coefficient, long long power) {
    polynomial *helper;
    if (coefficient == 0 && power == 0) {
        helper = nullptr;
    } else {
        helper = new polynomial;
        helper -> next = nullptr;
        helper -> coefficient = coefficient;
        helper -> power = power;
    }

    return helper;
}

polynomial *create_x() {
    return create_x(1, 1);
}

std::string show_error(const long long &pos) {
    std::string ans;
    for (long long i = 0; i < pos; ++i) {
        ans += ' ';
    }
    ans += '^';
    return ans;
}

void delete_polynomial(polynomial *&head) {
    polynomial *next;
    while (head != nullptr) {
        next = head -> next;
        delete head;
        head = next;
    }
}

void copy_specification(polynomial *copied, polynomial *copy) {
    copy -> power = copied -> power;
    copy -> coefficient = copied -> coefficient;
}

polynomial *copy_polynomial(polynomial *head) {
    polynomial *new_head, *new_now;
    new_head = nullptr;

    if (head != nullptr) {
        new_head = new_now = new polynomial;
        copy_specification(head, new_head);
        head = head -> next;

        while (head != nullptr) {
            new_now -> next = new polynomial;
            new_now = new_now -> next;
            copy_specification(head, new_now);
            head = head -> next;
        }
        new_now -> next = nullptr;
    }

    return new_head;
}

long long log_pow(long long number, long long power) {
    long long ans = 1;
    bool minus = (number < 0 && power % 2);
    while (power > 0) {
        ans *= ans;
        if (power % 2) {
            ans *= number;
        }
        power /= 2;
    }
    ans = std::abs(ans);
    if (minus) {
        ans *= -1;
    }
    return ans;
}

void print(polynomial *head, const std::string &sep, const std::string &end) {
    if (head == nullptr) {
        std::cout << 0;
    } else {
        if (head -> coefficient == -1 && head -> power != 0) {
            std::cout << '-';
        } else if (head -> coefficient != 1 || head -> power == 0 || head -> next == nullptr) {
            std::cout << head -> coefficient;
        }
        if (head -> power != 0) {
            std::cout << 'x';
            if (head -> power != 1) {
                std::cout << '^' << head -> power;
            }
        }
        head = head -> next;

        while (head != nullptr) {
            if (head -> coefficient > 0) {
                std::cout << sep << '+' << sep;
            } else {
                std::cout << sep << '-' << sep;
            }
            if (std::abs(head -> coefficient) != 1 || head -> power == 0) {
                std::cout << std::abs(head -> coefficient);
            }
            if (head -> power != 0) {
                std::cout << 'x';
                if (head -> power != 1) {
                    std::cout << '^' << head -> power;
                }
            }
            head = head -> next;
        }
    }
    std::cout << end;
}

void print(polynomial *head) {
    print(head, " ", "\n");
}

void reverse_string(std::string &str) {
    std::string rev_str;
    for (long long i = str.size() - 1; i >= 0; --i) {
        rev_str += str[i];
    }
    std::swap(str, rev_str);
}

std::string number_to_string(long long number) {
    std::string str_number, sign = "";
    if (number < 0) {
        sign += '-';
    }

    if (number == 0) {
        str_number += '0';
    }
    number = std::abs(number);
    while (number != 0) {
        str_number += (number % 10 + '0');
        number /= 10;
    }
    reverse_string(str_number);

    return sign + str_number;
}

std::string polynomial_to_string(polynomial *head, const std::string &sep, const std::string &end) {
    std::string ans;
    if (head == nullptr) {
        ans += '0';
    } else {
        if (head -> coefficient == -1 && head -> power != 0) {
            ans += '-';
        } else if (head -> coefficient != 1 || head -> power == 0) {
            ans += number_to_string(head -> coefficient);
        }
        if (head -> power != 0) {
            ans += 'x';
            if (head -> power != 1) {
                ans += '^' + number_to_string(head -> power);
            }
        }
        head = head -> next;

        while (head != nullptr) {
            if (head -> coefficient > 0) {
                ans += sep + '+' + sep;
            } else {
                ans += sep + '-' + sep;
            }
            if (std::abs(head -> coefficient) != 1 || head -> power == 0) {
                ans += number_to_string(std::abs(head -> coefficient));
            }
            if (head -> power != 0) {
                ans += 'x';
                if (head -> power != 1) {
                    ans += '^' + number_to_string(head -> power);
                }
            }
            head = head -> next;
        }
    }
    ans += end;

    return ans;
}

std::string polynomial_to_string(polynomial *head) {
    return polynomial_to_string(head, " ", "");
}
std::string polynomial_to_string(polynomial *head, const std::string &sep) {
    return polynomial_to_string(head, sep, "");
}

void print(std::stack <std::string> notation) {
    while (!notation.empty()) {
        std::cout << notation.top() << ' ';
        notation.pop();
    }
    std::cout << '\n';
}

bool is_same_sign(long long num_a, long long num_b) {
    return (num_a > 0 && num_b > 0) || (num_a < 0 && num_b < 0);
}

void merge(polynomial *&now_a, polynomial *&now_b, polynomial *now_new, bool minus) {
    polynomial *old_a, *old_b; // for throw
    old_a = old_b = nullptr;

    if (now_a != nullptr && now_b != nullptr) {
        now_new -> power = std::max(now_a -> power, now_b -> power);
    } else if (now_a != nullptr) {
        now_new -> power = now_a -> power;
    } else {
        now_new -> power = now_b -> power;
    }

    now_new -> coefficient = 0;
    if (now_a != nullptr && now_new -> power == now_a -> power) {
        now_new -> coefficient += now_a -> coefficient;
        old_a = now_a;
        now_a = now_a -> next;
    }
    if (now_b != nullptr && now_new -> power == now_b -> power) {
        if (minus) {
            now_new -> coefficient -= now_b -> coefficient;
        } else {
            now_new -> coefficient += now_b -> coefficient;
        }
        old_b = now_b;
        now_b = now_b -> next;
    }

    if (now_new != nullptr) { // Защита от длинной арифметики
        if (std::abs(now_new -> coefficient) > 36028797018963968) { // 2 ^ 55
            throw_error(0, "Вы хотите полезть в длинную арифметику. Это сложно, я не буду Вам в этом помогать. Пожалуйста, не надо этого больше делать. Это всё.");
        } else if (old_a != nullptr && old_b != nullptr) {
            if (is_same_sign(old_a -> coefficient, old_b -> coefficient)) {
                if ((!minus && (std::abs(now_new -> coefficient) < std::abs(old_a -> coefficient) || std::abs(now_new -> coefficient) < std::abs(old_b -> coefficient))) &&
                   (minus && (std::abs(now_new -> coefficient) > std::abs(old_a -> coefficient) && std::abs(now_new -> coefficient) > std::abs(old_b -> coefficient)))) {
                    throw_error(0, "Вы хотите полезть в длинную арифметику. Это сложно, я не буду Вам в этом помогать. Пожалуйста, не надо этого больше делать. Это всё.");
                }
            } else if ((!minus && (std::abs(now_new -> coefficient) > std::abs(old_a -> coefficient) && std::abs(now_new -> coefficient) > std::abs(old_b -> coefficient))) &&
                      (minus && (std::abs(now_new -> coefficient) < std::abs(old_a -> coefficient) || std::abs(now_new -> coefficient) < std::abs(old_b -> coefficient)))) {
                throw_error(0, "Вы хотите полезть в длинную арифметику. Это сложно, я не буду Вам в этом помогать. Пожалуйста, не надо этого больше делать. Это всё.");
            }
        }
    }
}

polynomial *plus_minus(polynomial *head_a, polynomial *head_b, bool minus) {
    /*
    if (head_a == nullptr && head_b == nullptr) {
        return nullptr;
    } else if (head_a == nullptr) {
        return copy_polynomial(head_b);
    } else if (head_b == nullptr) {
        return copy_polynomial(head_a);
    }
    */
    if (head_a == nullptr && head_b == nullptr) {
        return nullptr;
    } else if (head_a == nullptr) {
        if (minus) {
            polynomial *tmp_head, *now;
            tmp_head = now = copy_polynomial(head_b);

            while (now != nullptr) {
                now -> coefficient *= (-1);
                now = now -> next;
            }

            return tmp_head;
        } else {
            return copy_polynomial(head_b);
        }
    } else if (head_b == nullptr) {
        return copy_polynomial(head_a);
    }

    polynomial *head_new_polynomial, *new_polynomial, *prev_new_polynimial = nullptr;
    head_new_polynomial = new_polynomial = new polynomial;
    merge(head_a, head_b, head_new_polynomial, minus);

    while (head_a != nullptr || head_b != nullptr) {
        if (new_polynomial -> coefficient != 0) {
            new_polynomial -> next = new polynomial;
            prev_new_polynimial = new_polynomial;
            new_polynomial = new_polynomial -> next;
        }
        merge(head_a, head_b, new_polynomial, minus);
    }
    if (new_polynomial -> coefficient != 0) {
        new_polynomial -> next = nullptr;
    } else {
        delete new_polynomial;
        if (prev_new_polynimial != nullptr) {
            prev_new_polynimial -> next = nullptr;
        } else { // head_new_polynomial == new_polynomial
            new_polynomial = head_new_polynomial = nullptr;
        }
    }

    return head_new_polynomial;
}

void plus_minus_without_copy(polynomial *&head_a, polynomial *head_b, bool minus) {
    polynomial *new_head_a;
    new_head_a = plus_minus(head_a, head_b, minus);
    delete_polynomial(head_a);
    head_a = new_head_a;
}

void plus_minus_with_merge(polynomial *&head_a, polynomial *&head_b, bool minus) {
    plus_minus_without_copy(head_a, head_b, minus);
    delete_polynomial(head_b);
}

long long solve(polynomial *head, long long value) {
    long long ans = 0;
    while (head != nullptr) {
        ans += head -> coefficient * log_pow(value, head -> power);
        head = head -> next;
    }
    return ans;
}

bool equal(polynomial *head_a, polynomial *head_b) {
    while (head_a != nullptr && head_b != nullptr &&
           head_a -> power == head_b -> power && head_a -> coefficient == head_b -> coefficient) {
        head_a = head_a -> next;
        head_b = head_b -> next;
    }
    return (head_a == nullptr && head_b == nullptr);
}

void factor_polynomial(polynomial *head_a, long long coefficient, long long power) {
    while (head_a != nullptr) {
        head_a -> power += power;
        head_a -> coefficient *= coefficient;
        head_a = head_a -> next;
    }
}

polynomial *factor_polynomials(polynomial *head_a, polynomial *head_b) {
    polynomial *new_head, *tmp_head;
    new_head = nullptr;
    if (head_a != nullptr) {
        while (head_b != nullptr) {
            tmp_head = copy_polynomial(head_a);
            factor_polynomial(tmp_head, head_b -> coefficient, head_b -> power);
            plus_minus_without_copy(new_head, tmp_head, false);

            if (tmp_head == nullptr) {
                throw_error(0, "Вы хотите полезть в длинную арифметику. Это сложно, я не буду Вам в этом помогать. Пожалуйста, не надо этого больше делать. Это всё.");
            } else if ((std::abs(head_a -> coefficient) + std::abs(head_b -> coefficient) > 1e10)) { // ~2 ^ 32
                throw_error(0, "Вы хотите полезть в длинную арифметику. Это сложно, я не буду Вам в этом помогать. Пожалуйста, не надо этого больше делать. Это всё.");
            }
            /*
             * || ((std::abs(new_head -> coefficient) > 1125899906842624) ||
            (((head_a -> coefficient > 0) == (head_b -> coefficient > 0)) && head_a -> coefficient < new_head -> coefficient  && head_b -> coefficient < new_head -> coefficient) ||
            (!((head_a -> coefficient > 0) == (head_b -> coefficient > 0)) && head_a -> coefficient > new_head -> coefficient  && head_b -> coefficient > new_head -> coefficient))
            */

            delete_polynomial(tmp_head);

            head_b = head_b -> next;
        }
    }
    return new_head;
}

void factor_polynomials_without_copy(polynomial *&head_a, polynomial *head_b) {
    polynomial *new_head_a;
    new_head_a = factor_polynomials(head_a, head_b);
    delete_polynomial(head_a);
    head_a = new_head_a;
}

void factor_polynomials_with_merge(polynomial *&head_a, polynomial *&head_b) {
    factor_polynomials_without_copy(head_a, head_b);
    delete_polynomial(head_b);
}

polynomial *power_polynomial(polynomial *head, long long power) {
    if (head == nullptr) {
        if (power == 0) {
            return number_to_polynomial(1);
        } else if (power > 0) {
            return nullptr;
        } else {
            throw_error(1, "Мой создатель завещал мне, что на 0 делить нельзя");
        }
    } else if (std::abs(head -> coefficient) == 1 && head -> power == 0) {
        if (head -> coefficient == 1 || power % 2 == 0) {
            return create_x(1, 0);
        } else {
            return create_x(-1, 0);
        }
    } else if (power < 0) {
        throw_error(0, "Отрицательная степень к тёмной стороне ведёт (если многочлен не 1). А тёмная сторона - это вещественная арихметика.");
    } else if (power > 45) {
        throw_error(0, "Вы хотите полезть в длинную арифметику. Это сложно, я не буду Вам в этом помогать. Пожалуйста, не надо этого больше делать. Это всё.");
    } else {
        polynomial *new_head;
        new_head = number_to_polynomial(1);
        for (long long i = 0; i < power; ++i) {
            factor_polynomials_without_copy(new_head, head);
        }
        return new_head;
    }

    return nullptr;
}

void power_polynomial_without_copy(polynomial *&head, long long power) {
    polynomial *tmp_head;
    tmp_head = power_polynomial(head, power);
    std::swap(head, tmp_head);
    delete_polynomial(tmp_head);
}

void derivative(polynomial *now, polynomial *polynomial_member) {
    now -> power = polynomial_member -> power - 1;
    now -> coefficient = polynomial_member -> coefficient * polynomial_member -> power;
}

polynomial *find_derivative(polynomial *head) {
    polynomial *new_head, *new_now;
    new_head = new_now = nullptr;

    if (head != nullptr) {
        if (head -> power != 0) {
            new_head = new_now = new polynomial;
            derivative(new_head, head);
        }
        head = head -> next;

        while (head != nullptr) {
            if (head -> power != 0) {
                new_now -> next = new polynomial;
                new_now = new_now -> next;
                derivative(new_now, head);
            }
            head = head -> next;
        }
        if (new_now != nullptr) {
            new_now -> next = nullptr;
        }
    }
    return new_head;
}

void print_solves(list_solves *head) {
    while (head != nullptr) {
        std::cout << head -> solve << ' ';
        head = head -> next;
    }
    std::cout << '\n';
}

void delete_solves(list_solves *&head) {
    list_solves *next;
    while (head != nullptr) {
        next = head -> next;
        delete head;
        head = next;
    }
}

void add_solve(list_solves *&head, list_solves *&now, long long solve) {
    if (head == nullptr) {
        head = now = new list_solves;
    } else {
        now -> next = new list_solves;
        now = now -> next;
    }

    now -> solve = solve;
}

list_solves *find_int_solves(polynomial *head) {
    list_solves *head_solves, *now_solves;
    head_solves = now_solves = nullptr;

    polynomial *now;
    now = head;

    if (head == nullptr) {
        std::cout << "inf\n";
    } else {
        while (now -> next != nullptr) {
            now = now -> next;
        }

        long long sqrt_coefficient = std::sqrt(now -> coefficient);
        //std::cout << solve(head, 0);
        for (long long divider = 0; divider <= sqrt_coefficient; ++divider) {
            if (solve(head, divider) == 0) {
                add_solve(head_solves, now_solves, divider);
            }
            if (solve(head, -divider) == 0 && divider != 0) {
                add_solve(head_solves, now_solves, -divider);
            }
        }

        if (solve(head, now -> coefficient) == 0) {
            add_solve(head_solves, now_solves, now -> coefficient);
        }
        if (solve(head, -(now -> coefficient)) == 0) {
            add_solve(head_solves, now_solves, -(now -> coefficient));
        }

        if (now_solves != nullptr) {
            now_solves -> next = nullptr;
        }
    }

    return head_solves;
}

std::pair <polynomial*, polynomial*> division_polynomials(polynomial *head_dividable, polynomial *divider) {
    polynomial *dividable, *quotient, *mod;
    dividable = copy_polynomial(head_dividable);
    quotient = nullptr;

    if (divider == nullptr) {
        throw_error(1, "Мой создатель завещал мне, что на 0 делить нельзя");
        //error(0);
    }

    while (dividable != nullptr && dividable -> coefficient / divider -> coefficient == 0) {
        polynomial *dead;
        dead = dividable;
        dividable = dividable -> next;
        delete dead;
    }

    while (dividable != nullptr && dividable -> power >= divider -> power) {
        polynomial *helper_a, *helper_b;
        helper_a = copy_polynomial(divider);
        helper_b = create_x(dividable -> coefficient / divider -> coefficient,
                dividable -> power - divider -> power);
        plus_minus_without_copy(quotient, helper_b, false);
        factor_polynomials_with_merge(helper_a, helper_b);

        plus_minus_with_merge(dividable, helper_a, true);

        while (dividable != nullptr && dividable -> coefficient / divider -> coefficient == 0) {
            polynomial *dead;
            dead = dividable;
            dividable = dividable -> next;
            delete dead;
        }
    }
    if (dividable != nullptr) {
        delete_polynomial(dividable);
    }

    polynomial *helper;
    helper = factor_polynomials(quotient, divider);
    mod = plus_minus(head_dividable, helper, true);
    delete_polynomial(helper);

    return {quotient, mod};
}

void ignore_spaces(const std::string &str, long long &pos) {
    while (pos < str.size() && str[pos] == ' ') {
        ++pos;
    }
}

bool is_low_sign(const char &symbol) { // '-' || '+'
    return symbol == '-' || symbol == '+';
}

bool is_middle_sign(const char &symbol) { // '*' || '/'
    return symbol == '*' || symbol == '/';
}

bool is_high_sign(const char &symbol) { // '^'
    return symbol == '^';
}

bool is_math_sign(const char &symbol) {
    return is_low_sign(symbol) || is_middle_sign(symbol) || is_high_sign(symbol);
}

bool is_numeral(const char &symbol) {
    return '0' <= symbol && symbol <= '9';
}

bool is_number(const std::string &str, long long &pos) {
    if (pos < str.size() && is_numeral(str[pos])) {
        long long pos0 = pos;
        while (pos < str.size() && pos - pos0 < 19 && is_numeral(str[pos])) {
            ++pos;
        }
        if (pos - pos0 >= 14) {
            throw_error(0, "Вы хотите полезть в длинную арифметику. Это сложно, я не буду Вам в этом помогать. Пожалуйста, не надо этого больше делать. Это всё.");
        }
        ignore_spaces(str, pos);
        return true;
    } else {
        return false;
    }
}

bool is_variable(const char &symbol) {
    return symbol == 'x';
}

bool is_expression(const std::string &str, long long &pos, bool in_brackets);
bool is_expression_in_brackets(const std::string &str, long long &pos);

bool is_power(const std::string &str, long long &pos) {
    ignore_spaces(str, pos);
    if (pos < str.size() && str[pos] == '^') {
        ++pos;
        ignore_spaces(str, pos);
        if (is_expression_in_brackets(str, pos)) {
            do {
                ignore_spaces(str, pos);
                if (pos < str.size() && is_variable(str[pos])) {
                    ++pos;
                    ignore_spaces(str, pos);
                }
            } while (is_expression_in_brackets(str,pos));

            return true;
        } else if (is_number(str, pos)) {
             do {
                ignore_spaces(str, pos);
                if (pos < str.size() && is_variable(str[pos])) {
                    ++pos;
                    ignore_spaces(str, pos);
                }
             } while (is_expression_in_brackets(str,pos));

             return true;
        } else if (pos < str.size() && is_variable(str[pos])) {
            ++pos;
            ignore_spaces(str, pos);

            while (is_expression_in_brackets(str,pos)) {
                ignore_spaces(str, pos);
                if (pos < str.size() && is_variable(str[pos])) {
                    ++pos;
                    ignore_spaces(str, pos);
                }
            }

            return true;
        } else {
            //лажа exit
            throw_error(2, "Мы ожидали увидеть х, число или выражение в скобках, а не этот ужас", pos);
            //error(pos);
        }
    }
    return false;
}

bool is_member(const std::string &str, long long &pos) {
    ignore_spaces(str, pos);
    if (pos < str.size() && is_variable(str[pos])) {
        bool last_is_variable = true;
        ++pos;
        ignore_spaces(str, pos);
        while (is_expression_in_brackets(str, pos)) { // may exit
            last_is_variable = false;
            if (pos < str.size() && is_variable(str[pos])) {
                last_is_variable = true;
                ++pos;
                ignore_spaces(str, pos);
            }
        }

        if (!is_power(str, pos) && last_is_variable) { // may exit
            if (pos < str.size() && is_variable(str[pos])) {
                throw_error(2, "Да у Вас несколько x'ов подряд", pos);
            }
        }

        ignore_spaces(str, pos);
        return true;
    } else if (is_number(str, pos)) {
        bool last_is_variable = false;

        if (pos < str.size() && is_variable(str[pos])) {
            last_is_variable = true;
            ++pos;
            ignore_spaces(str, pos);
        }

        while (is_expression_in_brackets(str, pos)) { // may exit
            if (pos < str.size() && is_variable(str[pos])) {
                if (pos < str.size() && is_variable(str[pos])) {
                    ++pos;
                    ignore_spaces(str, pos);
                    last_is_variable = true;
                } else {
                    last_is_variable = false;
                }
            }
        }

        if (pos < str.size() && is_variable(str[pos])) {
            if (last_is_variable) {
                throw_error(2, "Да у Вас несколько x'ов подряд", pos);
                //error(pos);
            } else {
                ++pos;
                ignore_spaces(str, pos);
            }
        }

        if (pos < str.size() && is_power(str, pos)) { // may exit
            //++pos;
            //ignore_spaces(str, pos);
        }

        ignore_spaces(str, pos);
        return true;
    } else if (is_expression_in_brackets(str, pos)) {
        bool last_is_variable = true;
        do {
            if (pos < str.size() && is_variable(str[pos])) {
                ++pos;
                ignore_spaces(str, pos);
                last_is_variable = true;
            } else {
                last_is_variable = false;
            }
        } while (is_expression_in_brackets(str, pos));

        if (pos < str.size() && is_variable(str[pos])) {
            if (last_is_variable) {
                throw_error(2, "Да у Вас несколько x'ов подряд", pos);
                //error(pos);
            } else {
                ++pos;
                ignore_spaces(str, pos);
            }
        }

        if (pos < str.size() && is_power(str, pos)) { // may exit
            //++pos;
            //ignore_spaces(str, pos);
        }

        ignore_spaces(str, pos);
        return true;
    } else {
        throw_error(2, "Мы ожидали увидеть х, число или выражение в скобках, а не этот ужас", pos);
        //error(pos);
        return false;
        // error
    }
}

bool is_expression(const std::string &str, long long &pos, bool in_brackets) {
    //std::cerr << pos << '\n';
    ignore_spaces(str, pos);
    if (pos < str.size() && is_low_sign(str[pos])) {
        ++pos;
        ignore_spaces(str, pos);
    }

    if (in_brackets) {
        bool ans = is_member(str, pos);
        while (pos < str.size() && ans && str[pos] != ')') {
            if (is_math_sign(str[pos]) && !is_high_sign(str[pos])) {
                ++pos;
                ans = is_member(str, pos);
                ignore_spaces(str, pos);
            } else {
                if (is_high_sign(str[pos])) {
                    throw_error(2, "Мы не любим каскадное возведение в степень (уберите '^' или используйте скобки)", pos);
                } else {
                    throw_error(2, "Мы ожидали увидеть какой-нибудь математический знак, а не это недоразумение", pos);
                }
                //error(pos);
            }
        }
        return ans && pos < str.size();
    } else {
        //std::cerr << "xxx: " << pos << '\n';
        bool ans = is_member(str, pos);
        // << "xxxL " << pos << '\n';
        while (pos < str.size() && ans) {
            if (is_math_sign(str[pos]) && !is_high_sign(str[pos])) {
                ++pos;
                ans = is_member(str, pos);
            } else {
                if (is_high_sign(str[pos])) {
                    throw_error(2, "Мы не любим каскадное возведение в степень (уберите '^' или используйте скобки)", pos);
                } else {
                    std::cout << "xxx2" << ' ' << pos << std::endl << str << std::endl << show_error(pos) << std::endl;
                    throw_error(2, "Мы ожидали увидеть какой-нибудь математический знак, а не это недоразумение", pos);
                }
                //error(pos);
            }
        }
        return ans;
    }

}

bool is_expression_in_brackets(const std::string &str, long long &pos) {
    ignore_spaces(str, pos);
    if (pos < str.size() && str[pos] == '(') {
        ++pos;
        if (is_expression(str, pos, true)) {
            ++pos;
            ignore_spaces(str, pos);
            return true;
        } else {
            //нет закрывающей скобки
            throw_error(2, "Куда Вы дели закрывающую скобку ( ')' )?", pos);
            //std::cout << ')';
            //error(pos);
        }
    }
    return false;
}

void delete_spaces(std::string &str) {
    std::string new_str;
    for (char i : str) {
        if (i != ' ') {
            new_str += i;
        }
    }
    std::swap(str, new_str);
}

bool check_grammar(const std::string &str) {
    long long pos = 0;
    ignore_spaces(str, pos);
    if (pos < str.size()) {
        return is_expression(str, pos, false);
    } else {
        if (pos == 0) {
            throw("Пустая строка. Какой в этом смысл?");
        } else {
            throw("Только пробелы. Какой в этом смысл?");
        }
    }
}

int priority_of_sign(const char &symbol) {
    if (is_low_sign(symbol)) {
        return 0;
    } else if (is_middle_sign(symbol)) {
        return 1;
    } else if (is_high_sign(symbol)) {
        return 2;
    } else {
        return 3;
    }
}

void reverse_stack(std::stack <std::string> &notation) {
    std::stack <std::string> reverse_notation;
    while (!notation.empty()) {
        reverse_notation.push(notation.top());
        notation.pop();
    }
    std::swap(reverse_notation, notation);
}

std::string to_string(const char &symbol) {
    std::string str;
    str.push_back(symbol);
    return str;
}

std::stack <std::string> to_postfix_notation(const std::string &expression) {
    std::stack <std::string> postfix_notation;
    std::stack <char> operations;

    for (long long pos = 0; pos < expression.size();) {
        if (is_math_sign(expression[pos])) {
            if (is_low_sign(expression[pos]) && (pos == 0 || (pos - 1 >= 0 && expression[pos - 1] == '(')) &&
            pos + 1 < expression.size() && (is_numeral(expression[pos + 1]) || is_variable(expression[pos + 1]) ||
            expression[pos + 1] == '(')) {
                std::string string_number;
                if (expression[pos] == '-') {
                    postfix_notation.push("-1");
                } else {
                    postfix_notation.push("1");
                }
                ++pos;
                if (is_numeral(expression[pos])) {
                    while (pos < expression.size() && is_numeral(expression[pos])) {
                        string_number.push_back(expression[pos]);
                        ++pos;
                    }
                    postfix_notation.push(string_number);

                    if (pos < expression.size() && expression[pos] == 'x') {
                        postfix_notation.push("x");
                        operations.push('*');
                        ++pos;
                    }
                } else if (is_variable(expression[pos])){
                    string_number += 'x';
                    postfix_notation.push(string_number);
                    ++pos;
                }
                operations.push('*');
            } else {
                while (!operations.empty() && priority_of_sign(operations.top()) >= priority_of_sign(expression[pos]) &&
                       operations.top() != '(') {
                    postfix_notation.push(to_string(operations.top()));
                    operations.pop();
                }
                operations.push(expression[pos]);
                ++pos;
            }
        } else if (expression[pos] == ')') {
            while (operations.top() != '(') {
                postfix_notation.push(to_string(operations.top()));
                operations.pop();
            }
            operations.pop();
            ++pos;
        } else if (is_numeral(expression[pos])) {
            std::string string_number;
            while (pos < expression.size() && is_numeral(expression[pos])) {
                string_number.push_back(expression[pos]);
                ++pos;
            }
            postfix_notation.push(string_number);
            if (pos < expression.size() && expression[pos] == 'x') {
                postfix_notation.push("x");
                operations.push('*');
                ++pos;
            }
        } else if (expression[pos] == 'x') {
            if (pos - 1 >= 0 && expression[pos - 1] == ')') {
                operations.push('*');
            }
            postfix_notation.push(to_string(expression[pos]));
            ++pos;
        } else if (expression[pos] == '(') {
            if (pos - 1 >= 0 && (is_variable(expression[pos - 1]) || expression[pos - 1] == ')' ||
            is_numeral(expression[pos - 1]))) {
                operations.push('*');
            }
            operations.push(expression[pos]);
            ++pos;
        }
    }
    while (!operations.empty()) {
        postfix_notation.push(to_string(operations.top()));
        operations.pop();
    }

    reverse_stack(postfix_notation);
    return postfix_notation;
}

long long string_to_number(const std::string &str_number) {
    long long number = 0, i = 0;

    if (str_number[i] == '-') {
        ++i;
    }

    for (; i < str_number.size(); ++i) {
        number = number * 10 + (str_number[i] - '0');
    }

    if (str_number[0] == '-') {
        number *= -1;
    }

    return number;
}

polynomial *postfix_notation_to_polynomial(std::stack <std::string> postfix_notation) {
    std::stack <polynomial*> ans;
    polynomial *helper_a, *helper_b;

    while (!postfix_notation.empty()) {
        if (postfix_notation.top().size() == 1 && (is_math_sign(postfix_notation.top()[0]))) {
            if (ans.size() == 1) {
                if (postfix_notation.top() == "-") {
                    helper_a = ans.top();
                    ans.pop();
                    helper_b = number_to_polynomial(-1);
                    factor_polynomials_with_merge(helper_a, helper_b);
                    ans.push(helper_a);
                }
            } else {
                helper_b = ans.top();
                ans.pop();
                helper_a = ans.top();
                ans.pop();
                if (is_low_sign(postfix_notation.top()[0])) {
                    plus_minus_with_merge(helper_a, helper_b,postfix_notation.top() == "-");
                } else if (is_middle_sign(postfix_notation.top()[0])) {
                    if (postfix_notation.top() == "*") {
                        factor_polynomials_with_merge(helper_a, helper_b);
                    } else {
                        if (helper_b == nullptr) {
                            throw_error(1, "Мой создатель завещал мне, что на 0 делить нельзя");
                        }
                        std::pair <polynomial*, polynomial*> div_mod = division_polynomials(helper_a, helper_b);
                        if (div_mod.second == nullptr) {
                            delete_polynomial(helper_a);
                            delete_polynomial(helper_b);

                            helper_a = div_mod.first;
                        } else {
                            throw_error(0, "Вы хотите лезть в вещественную арихметику.\nСтрашные воспоминания о вещественном бинарном поиске всё ещё живы в нас, поэтому мы не желаем с этим мучиться");
                            //error(0);
                        }
                    }
                } else {
                    if (helper_b != nullptr && helper_b -> power == 0) {
                        power_polynomial_without_copy(helper_a, solve(helper_b, 0));
                    } else if (helper_b == nullptr) {
                        power_polynomial_without_copy(helper_a, 0);
                    } else {
                        throw_error(0, "Вы хотите использовать переменную степень. Для нас это слишком сложно");
                        //error(0);
                    }
                }
                ans.push(helper_a);
            }
        } else if (postfix_notation.top() == "x" || postfix_notation.top() == "-x") {
            if (postfix_notation.top()[0] == '-') {
                ans.push(create_x(-1, 1));
            } else {
                ans.push(create_x());
            }
        } else {
            ans.push(number_to_polynomial(string_to_number(postfix_notation.top())));
        }
        if (!ans.empty() && ans.top() != nullptr && ans.top() != nullptr) {
            if (std::abs(ans.top() -> coefficient) > 36028797018963968) { // 2 ^ 55
                throw_error(0, "Вы хотите полезть в длинную арифметику. Это сложно, я не буду Вам в этом помогать. Пожалуйста, не надо этого больше делать. Это всё.");
            }
        }
        postfix_notation.pop();
    }

    return ans.top();
}
