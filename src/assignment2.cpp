// Arithmetic Expression Evaluator

#include"myTL/Stack.h"
#include<iostream>
#include<string>
#include<sstream>

/**
 * @brief infix expression을 postfix expression으로 변환, postfix expression을 evaluate.
 */
class Evaluator{
public:
// Evaluator은 static class이므로,
// 따로 생성자 필요x
    Evaluator()=delete;

    /**
     * @brief std::cin에서 expression을 읽고, 변환하기 좋은 형태로 변환.
     * 
     * @return std::string 
     */
    static std::string read_expression(void){
        std::string raw;
        std::cout<<"infix expression: ";
        std::getline(std::cin, raw);

        std::stringstream result;
        // '('로 시작해야, 전체 표현식의 끝을 알기 쉬움.
        result<<" ( ";
        for(char c:raw){
            switch(c){
            case '+':
            case '-':
            case '*':
            case '/':
            case '(':
            case ')':
            // 모든 operator과 operand가 ' '으로 구분되도록.
                result<<' '<<c<<' ';
            case ' ':
            // user input으로 들어온 ' '는 무시.
                break;
            default:
            // operand 출력.
                result<<c;
            }
        }
        // 전체 표현식의 끝을 의미하는 ')' 추가.
        result<<" ) ";
        return result.str();
    }
public:
    /**
     * @brief infix expression을 postfix expression으로 변환
     * 
     * @param infix operator, operand는 ' '로 구분, 전체식은 괄호로 감싸져있어야함.
     * @return postfix expression
     */
    static std::string convert_to_postfix(std::string infix){
        std::stringstream buffer;

        My::Stack<char> operators;
        std::string operand;
        
        for(char c:infix){
            switch(c){
            case '+':
            case '-':
            // 가장 우선순위가 낮으므로 '+'나 '-'를 만났다는 것은,
            // (괄호를 제외한, 이전에 stack에 넣어진 operator에 관한)
            // sub-expression들이 완전하다는 뜻.
            //
            // Example
            //
            // 1 + ( 3 + 4 * 6 - 7 )
            //                 ^ 를 만났을 때,
            // 3 + 4 * 6 은 완전함. (이때, 3 + 4 * 6을 sub-expression이라 칭함.)
            // => 3 4 6 * + 로 완전히 표현 가능.
                while(!operators.empty()){
                    // '('을 빼지 않도록 top() 사용.
                    char op=operators.top();
                    if(op!='('){
                        buffer<<operators.pop()<<' ';
                    } else break;
                }
            case '*':
            case '/':
            case '(':
                operators.push(c);
            break;

            case ' ':
            // ' '로 operator과 operand를 구분하므로,
            // operand의 바로 다음 ' '을 만나면 operand가 끝났다는 뜻.
                if(!operand.empty()){
                    buffer<<operand<<' ';
                    operand.clear();

                    switch(operators.top()){
                    // '*' 와 '/'는 가장 우선 순위가 높으므로,
                    // lhs * rhs 에서 rhs가 완성되면
                    // lhs * rhs 는 완전함. 
                    case '*':
                    case '/':
                        buffer<<operators.pop()<<' ';
                    }
                }
            break;

            case ')':
            // 괄호 내부의 sub-expression이 완전함.
                char op;
                while((op=operators.pop())!='('){
                    buffer<<op<<' ';
                }
            break;

            default:
            // operand를 저장.
                operand+=c;
            }
        }

        return buffer.str();
    }

    static double evaluate_postfix(std::string postfix) {
        std::string operand;
        My::Stack<double> operands;
        My::Stack<char> operators;


        for(char c:postfix){
            switch(c){
            case '+':
            case '-':
            case '*':
            case '/':{
            // 먼저 pop되는 게 우측에 와야 함.
                double rhs=operands.pop();
                double lhs=operands.pop();
                double result=0;
                switch(c){
                case '+':
                    result=lhs+rhs;
                break;
                case '-':
                    result=lhs-rhs;
                break;
                case '*':
                    result=lhs*rhs;
                break;
                case '/':
                    assert(rhs!=0 && "divide by Zero");
                    result=lhs/rhs;
                }
                operands.push(result);
            break;
            }
            case ' ':
                if(!operand.empty()){
                    std::stringstream ss(operand);
                    double value=0;
                    ss>>value;
                    if(ss.fail()){
                    // operand가 double로 변환 불가. -> 따로 입력으로 받음.
                        std::cout<<operand<<"? ";
                        std::cin>>value;
                        ss.clear();
                    }
                    operands.push(value);
                    operand.clear();
                }
            break;

            default:
            // operand를 저장.
                operand+=c;
            }
        }

        return operands.pop();
    }
};

int main(void){
    std::string infix=Evaluator::read_expression();
    std::cout<<"infix expression: "<<infix<<std::endl;

    std::string postfix=Evaluator::convert_to_postfix(infix);
    std::cout<<"postfix expression: "<<postfix<<std::endl;

    double result=Evaluator::evaluate_postfix(postfix);    
    std::cout<<"Result: "<<result<<std::endl;

    return 0;
}