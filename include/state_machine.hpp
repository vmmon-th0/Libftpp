#ifndef STATE_MACHINE_HPP
#define STATE_MACHINE_HPP

#include <unordered_set>
#include <unordered_map>
#include <functional>
#include <stdexcept>
#include <optional>

// We use this hash function since we are operating on a non-primitive type that unordered map cannot hash.
// https://quantum5.ca/2019/04/05/using-unordered-data-structures-on-std-pair-cpp/

struct pair_hash
{
    template <class T1, class T2>
    std::size_t operator()(const std::pair<T1, T2>& pair) const
    {
        return std::hash<T1>()(pair.first) ^ std::hash<T2>()(pair.second);
    }
};

template <typename TState> class StateMachine
{
    public:
        StateMachine() = default;
        ~StateMachine() = default;

        void addState(const TState &state)
        {
            _states.insert(state);
        }

        void addTransition(const TState &startState, const TState &endState, const std::function<void()> &action)
        {
            checkStateExists(startState);
            checkStateExists(endState);
            _transitions[{startState, endState}] = action;
        }

        void addAction(const TState &state, const std::function<void()> &action)
        {
            checkStateExists(state);
            _actions[state] = action;
        }

        TState getCurrentState() const
        {
            if (!_currentState)
            {
                throw std::runtime_error("Current state is not set.");
            }
            return *_currentState;
        }

        void transitionTo(const TState &nextState)
        {
            if (!_currentState)
            {
                throw std::runtime_error("Current state is not set. Cannot transition.");
            }

            checkStateExists(nextState);

            auto key = std::make_pair(*_currentState, nextState);
            auto it = _transitions.find(key);
            if (it == _transitions.end())
            {
                throw std::runtime_error("Transition not defined.");
            }

            it->second();
            _currentState = nextState;
        }

        void setInitialState(const TState &state)
        {
            checkStateExists(state);
            _currentState = state;
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
        void checkStateExists(const TState &state) const
        {
            if (_states.find(state) == _states.end())
            {
                throw std::runtime_error("State not registered.");
            }
        }

        std::unordered_set<TState> _states;
        std::unordered_map<std::pair<TState, TState>, std::function<void()>, pair_hash> _transitions;
        std::unordered_map<TState, std::function<void()>> _actions;
        std::optional<TState> _currentState;
};

#endif