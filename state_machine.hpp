#ifndef STATE_MACHINE_HPP
#define STATE_MACHINE_HPP

#include "data_structures.hpp"

template<typename TState>
class StateMachine
{
    public:
        StateMachine() = default;
        ~StateMachine() = default;

        void addState(const TState& state)
        {
            _states.insert(state);
        }

        void addTransition(const TState& startState, const TState& endState, const std::function<void()>& action)
        {
            ensureStateExists(startState);
            ensureStateExists(endState);
            _transitions[{startState, endState}] = action;
        }

        void addAction(const TState& state, const std::function<void()>& action)
        {
            ensureStateExists(state);
            _actions[state] = action;
        }

        void setInitialState(const TState& state)
        {
            ensureStateExists(state);
            _currentState = state;
        }

        TState getCurrentState() const
        {
            if (!_currentState)
            {
                throw std::runtime_error("Current state is not set.");
            }
            return *_currentState;
        }

        void transitionTo(const TState& nextState)
        {
            if (!_currentState)
            {
                throw std::runtime_error("Current state is not set. Cannot transition.");
            }

            ensureStateExists(nextState);

            auto key = std::make_pair(*_currentState, nextState);
            auto it = _transitions.find(key);
            if (it == _transitions.end())
            {
                throw std::runtime_error("Transition not defined.");
            }

            it->second();
            _currentState = nextState;
        }

        void update()
        {
            if (!_currentState)
            {
                throw std::runtime_error("Current state is not set. Cannot update.");
            }

            auto it = _actions.find(*_currentState);
            if (it == _actions.end())
            {
                throw std::runtime_error("Action for current state not defined.");
            }

            it->second();
        }

    private:
        void ensureStateExists(const TState& state) const
        {
            if (_states.find(state) == _states.end())
            {
                throw std::runtime_error("State not registered.");
            }
        }

        std::unordered_set<TState> _states;
        std::unordered_map<std::pair<TState, TState>, std::function<void()>> _transitions;
        std::unordered_map<TState, std::function<void()>> _actions;
        std::optional<TState> _currentState;
};

#endif