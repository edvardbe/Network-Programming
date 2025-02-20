package no.ntnu.idi.compiler.service;

import org.springframework.stereotype.Service;


import net.objecthunter.exp4j.Expression;
import net.objecthunter.exp4j.ExpressionBuilder;

@Service
public class CompilerService {

    public double compile(String expression) {
        String[] fracs = expression.split("/");
        int nFracs = fracs.length;

        for (int i = 1; i < nFracs; i++) {
            System.out.println(fracs[i]);
            Expression frac = new ExpressionBuilder(fracs[i]).build();
            
            double num = frac.evaluate();
            if (num == 0) throw new ArithmeticException("Divide by zero");
        }
        Expression e = new ExpressionBuilder(expression).build();
        return e.evaluate();
    }

}
