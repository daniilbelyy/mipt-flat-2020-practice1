#include<iostream>
#include<stack>
#include<unordered_set>
#include<cstring>
#include<algorithm>

enum answers { YES, NO, ERROR };

int Gcd(int a, int b) {
    
    if (b == 0) {
    return a;
    }

    return Gcd(b, a % b);
}

std::unordered_set<int> Mult(const std::unordered_set<int>& first, const std::unordered_set<int>& second, int modulo) {
    std::unordered_set<int> result;

    for (const auto& number_first : first) {

        for (const auto& number_second : second) {
            result.insert((number_first + number_second) % modulo);
        }

    }

    return result;
}

std::unordered_set<int> Plus(const std::unordered_set<int>& first, const std::unordered_set<int>& second, int modulo) {
    std::unordered_set<int> result;

    for (const auto& number : first) {
        result.insert(number);
    }
    for (const auto& number : second) {
        result.insert(number);
    }
    return result;
}

std::unordered_set<int> Star(const std::unordered_set<int>& first, int modulo) {
    std::unordered_set<int> result;
    auto min_it = first.begin();
    int first_elem = *min_it;
    int min_number = -1;

    if (first_elem == 0) {
        ++min_it;
    }

    if (min_it != first.end()) {
        min_number = *min_it;

        for (auto it = ++min_it; it != first.end(); ++it) {

            if (*it) {
                min_number = Gcd(min_number, *it);

                if (min_number == 1) {
                    break;
                }

            }

        }

    }

    min_number = Gcd(modulo, min_number);
    result.insert(0);

    if (min_number > -1) {
        int number = 0;

        do {
            result.insert(number);
            number = (number + min_number) % modulo;
        } while (number != 0);

    }

    return result;
}

answers CountModulo(const std::string& regular, char symb, const size_t modulo) {
    std::stack<std::unordered_set<int>> pieces;

    for (int i = 0; i < regular.size(); ++i) {

        if (regular[i] == symb) {
            std::unordered_set<int> piece;
            pieces.push({ 1 });
        }

        else if (regular[i] == '.') {

            if (pieces.size() < 2) {
                return ERROR;
            }

            const auto first = pieces.top();
            pieces.pop();
            const auto second = pieces.top();
            pieces.pop();
            pieces.push(Mult(first, second, modulo));
        }

        else if (regular[i] == '+') {

            if (pieces.size() < 2) {
                return ERROR;
            }

            const auto first = pieces.top();
            pieces.pop();
            const auto second = pieces.top();
            pieces.pop();
            pieces.push(Plus(first, second, modulo));
        }

        else if (regular[i] == '*') {

            if (pieces.size() < 1) {
                return ERROR;
            }

            const auto first = pieces.top();
            pieces.pop();
            pieces.push(Star(first, modulo));
        }

        else {
            pieces.push({ 0 });
        }

    }

    if (pieces.size() > 1) {
        return ERROR;
    }

    auto answer = pieces.top();

    if (answer.find(0) != answer.end()) {
        return YES;
    }

    else {
        return NO;
    }

}

int main() {
    std::string regular;
    int modulo;
    char symb;
    std::cin >> regular >> symb >> modulo;
    auto answer = CountModulo(regular, symb, modulo);

    if (answer == YES) {
        std::cout << "YES";
    }

    else if (answer == NO) {
        std::cout << "NO";
    }

    else {
        std::cout << "ERROR";
    }

    return 0;
}
