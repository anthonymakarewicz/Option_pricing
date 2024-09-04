# Option Pricing Project Structure

```plaintext
src
├── market_data
│   ├── interface_market_data.h
│   ├── market_data.h
│   ├── market_data_observer.h
│   └── stock_data.h
├── model
│   ├── base_model.h
│   ├── bates_model.h
│   ├── discretization
│   │   ├── base_cir_discretization.h
│   │   ├── explicit_euler_cir_discretization.h
│   │   └── milstein_cir_discretization.h
│   ├── gbm_model.h
│   ├── heston_model.h
│   ├── kou_model.h
│   ├── merton_jump_diffusion_model.h
│   └── variance_gamma_model.h
├── numerical_analysis
│   ├── basis_function
│   │   ├── base_basis_function.h
│   │   ├── chebyshev.h
│   │   ├── laguerre.h
│   │   ├── legendre.h
│   │   └── monomial.h
│   ├── interpolation
│   │   ├── base_interpolation.h
│   │   ├── linear_interpolation.h
│   │   └── quadratic_interpolation.h
│   ├── linear_algebra
│   │   └── matrix_solver
│   │       ├── base_matrix_solver.h
│   │       ├── lu_decomposition.h
│   │       ├── partial_pivoting_lu_decomposition.h
│   │       └── thomas_algorithm.h
│   └── regression
│       ├── base_regression.h
│       ├── lasso.h
│       ├── least_squares.h
│       └── ridge.h
├── option
│   ├── base_factory_option.h
│   ├── base_option.h
│   ├── interface_option.h
│   ├── parameter_object.h
│   ├── path_dependent
│   │   ├── american_option.h
│   │   ├── asian_option.h
│   │   ├── barrier_option.h
│   │   ├── base_path_dependent_option.h
│   │   ├── factory_american_option.h
│   │   ├── factory_asian_option.h
│   │   ├── factory_barrier_option.h
│   │   ├── factory_lookback_option.h
│   │   └── lookback_option.h
│   └── single_path
│       ├── base_single_path_option.h
│       ├── digital_option.h
│       ├── double_digital_option.h
│       ├── european_option.h
│       ├── factory_digital_option.h
│       ├── factory_double_digital_option.h
│       └── factory_european_option.h
├── payoff
│   ├── base_payoff.h
│   ├── double_strikes
│   │   ├── base_payoff_double_strikes.h
│   │   └── payoff_double_digital.h
│   ├── payoff_floating_strike_lookback.h
│   └── single_strike
│       ├── base_payoff_single_strike.h
│       ├── payoff_digital.h
│       └── payoff_vanilla.h
├── random
│   ├── distribution
│   │   ├── base_distribution.h
│   │   ├── continuous_uniform_distrib.h
│   │   ├── exponential_distr.h
│   │   ├── gamma_distrib.h
│   │   ├── normal_distrib.h
│   │   ├── poisson_distrib.h
│   │   └── standard_normal_distribution.h
│   └── number_generator
│       ├── base_generator.h
│       ├── base_quasi_random_generator.h
│       ├── faure_quasi_random_generator.h
│       ├── pseudo_random_generator.h
│       └── sobol_quasi_random_generator.h
└── solver
    ├── base_solver.h
    ├── finite_difference_method
    │   ├── pde
    │   │   ├── multi_factor
    │   │   │   └── base_convection_diffusion_pde.h
    │   │   └── one_factor
    │   │       ├── base_convection_diffusion_pde.h
    │   │       └── black_scholes_pde.h
    │   └── solver
    │       ├── multi_factor
    │       │   ├── base_fdm_solver.h
    │       │   ├── crank_nicolson_fdm_solver.h
    │       │   ├── euler_explicit_fdm_solver.h
    │       │   └── euler_implicit_fdm_solver.h
    │       └── one_factor
    │           ├── base_fdm_solver.h
    │           ├── crank_nicolson_fdm_solver.h
    │           ├── euler_explicit_fdm_solver.h
    │           └── euler_implicit_fdm_solver.h
    └── monte_carlo
        ├── base_mc.h
        ├── builder
        │   ├── base_mc_builder.h
        │   ├── mc_builder_american.h
        │   ├── mc_builder_asian.h
        │   ├── mc_builder_barrier.h
        │   ├── mc_builder_lookback.h
        │   └── mc_builder_single_path.h
        ├── mc_american.h
        ├── mc_asian.h
        ├── mc_barrier.h
        ├── mc_lookback.h
        ├── mc_single_path.h
        └── mc_solver.h
```