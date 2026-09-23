add_executable(QuasigroupExperiments main.cpp
        QuasigroupExperiments.h
        AllAlgorithmsExperiment.cpp
        AssociativityExperiment.cpp
        AffinityExperiments.cpp)
target_link_libraries(QuasigroupExperiments PRIVATE Quasigroup::QuasigroupLib)