#include "FormalProof.h"
#include <cassert>
#include <stdexcept>
#include <iostream>
#include <unordered_set>
#include <ranges>

FormalProof::FormalProof(Node* root): root(root), depth(0) {
    setPremiseConclusion();
    if (root->type == CON) {
        conditionalProof();
    }
}

FormalProof::FormalProof(Node* root, int depth): root(root), depth(depth) {
    setPremiseConclusion();
    if (root->type == CON) {
        conditionalProof();
    }
}

FormalProof::Step::Step(Node* expression, Rule rule, int depth):
    expression(expression), rule(rule), depth(depth) {}

void FormalProof::setPremiseConclusion() {
    assert(root && "root has not has not been initialized");

    switch (root->type) {
        case VAR: premise = conclusion = root;
                  break;
        case CON: premise = root->left;
                  conclusion = root->right;
                  break;
        case BICON: // TODO
                  break;
        default: throw std::runtime_error("Incorrect root Type");
    }
}

void FormalProof::conditionalProof() {
    toProve.push(root->right);

    Step* assumption;
    if (steps.empty()) {
        assumption = new Step(root->left, ASSUMPTION, 0);
    }

    steps.push_back(assumption);
    assumptions.push_back(assumption);

    prove();
}

void FormalProof::prove() {
    while (!toProve.empty()) {
        Node* goal = toProve.front();

        if (goal->type == OR) {
            proveOR();
        }
    }
}

void FormalProof::proveOR() {

}


bool FormalProof::satisfiesRule(const std::vector<Step*> procedure, const Step* lastStep) const {
    /**
     * @note All cases will traverse through @param procedure and make sure that any
     * steps made to support @param lastStep have a depth less than or equal to it.
     * 
     * @note This method assumes that all Steps in procedure are valid.
     */

    switch (lastStep->rule) {
        case NOTintro: 
            /**
             * Check if an assumption equal to right Node of @param lastStep
             * is made, then a contradiction is found.
             */
            return false;
        case ANDintro:
            /**
             * Checks that the left and right Node's of @param lastStep's expression
             * appear as steps in @param procedure.
             */
            return checkANDintro(procedure, lastStep);
        case ORintro:
            /**
             * Checks that either the left or right Node's of @param lastStep's expression
             * appear as steps in @param procedure.
             */
            return checkORintro(procedure, lastStep);
        case CONintro:
            /**
             * Check that an assumption equal to the left Node of @param lastStep's expression
             * is made, then the consequent is proven.
             */
            return false;
        case BICONintro:
            /**
             * Check for CONintro in both directions.
             */
            return false;
        case CONTRADICTIONintro:
            /**
             * Two Steps exist in procedure, where one is a negation of another.
             */
            return false;
        case NOTelim:
            /** 
             * Check if double negation of @param lastStep exists.
             */
            return false;
        case ANDelim:
            /**
             * Check that a Step with an AND expression exist containing 
             * @param lastStep's expression in its left or right Node.
             */
            return false;
        case ORelim:
            /**
             * Proof by cases: Check that left and right Nodes of an OR
             * Node of a Step both result in @param lastStep's expression.
             */
            return false;
        case CONelim:
            /**
             * Check that a Step contains @param lastStep's expression
             * as the antecedent of a CON Node and there is another step
             * containing the precedent .
             */
            return false;
        case BICONelim:
            /**
             * Check that a Step contains @param lastStep's expression
             * as as a child of a BICON Node and there is another step
             * containing the other child Node.
             */
            return false;
        case CONTRADICTIONelim:
            /**
             * Check that there is a step with a CONTRADICTION expression.
             */
            return false;
        default:
            throw std::runtime_error("Invalid Rule");
    }
}

/**
 * @todo Update to fix else if clause to check if step->expression == negate(lastStep->expression)
 */
bool FormalProof::checkNOTintro(const std::vector<Step*> procedure, const Step* lastStep) const {
    bool foundAssumption = false;
    int lastStepDepth = lastStep->depth;

    for (const auto& step : procedure) {
        if (foundAssumption) {
            if (step->depth <= lastStepDepth) {
                foundAssumption = false;
            } else if (step->depth == lastStepDepth + 1 && step->rule == CONTRADICTIONintro) {
                return true;
            }
        } else if (step->depth == lastStepDepth && step->rule == ASSUMPTION && 
                   lastStep->expression->type == NOT && lastStep->expression->right == step->expression) {
            foundAssumption = true;
        }
    }
    return false;
}

bool FormalProof::checkANDintro(const std::vector<Step*> procedure, const Step* lastStep) const {
    std::unordered_set<Node*> toFind = {lastStep->expression->left, lastStep->expression->right};
    std::unordered_set<Node*> found;

    int lastStepDepth = lastStep->depth;

    std::for_each(procedure.begin(), procedure.end(), [&](Step* step) {
        if (step->depth <= lastStepDepth && toFind.count(step->expression)) {
            found.insert(step->expression);
        }
    });
    return found.size() == 2;
}

bool FormalProof::checkORintro(const std::vector<Step*> procedure, const Step* lastStep) const {
    std::unordered_set<Node*> toFind = {lastStep->expression->left, lastStep->expression->right};
    std::unordered_set<Node*> found;

    int lastStepDepth = lastStep->depth;

    std::for_each(procedure.begin(), procedure.end(), [&](Step* step) {
        if (step->depth <= lastStepDepth && toFind.count(step->expression)) {
            found.insert(step->expression);
        }
    });
    return found.size() > 0;
}

/** 
 * @todo
*/
bool FormalProof::checkCONintro(const std::vector<Step*> procedure, const Step* lastStep) const {
    Node* antecedent = lastStep->expression->left;
    Node* consequent = lastStep->expression->right;

    int lastStepDepth = lastStep->depth;

    return false;
}

/**
 * @todo
 */
bool FormalProof::checkCONTRADICTIONintro(const std::vector<Step*> procedure, const Step* lastStep) const {
    return false;
}


bool FormalProof::checkNOTelim(const std::vector<Step*> procedure, const Step* lastStep) const {
    for (const auto & step : std::ranges::reverse_view(procedure)) {
        if (step->depth > lastStep->depth) continue;

        Node* expr = step->expression;
        // Check if step's expression is a double negation of lastStep's expression
        if (expr->type == NOT && expr->right->type == NOT && expr->right->right == lastStep->expression)
            return true;
    }
    return false;
}

bool FormalProof::checkANDelim(const std::vector<Step*> procedure, const Step* lastStep) const {
    for (const auto & step : std::ranges::reverse_view(procedure)) {
        if (step->depth > lastStep->depth) continue;

        Node* expr = step->expression;
        if (expr->type == AND && (expr->left == lastStep->expression || expr->right == lastStep->expression))
            return true;
    }
    return false;
}