# Paper Notes

Maybe in final remarks?
- great application: PPL since we have to differentiate log-pdf

## Reverse-mode Automatic Differentiation
unique aspects of my library:
Further Studies: GPU support and higher-order derivatives

## Benchmark

Memory consumption benchmark for stochastic volatility:

Rough estimate for STAN is as follows:
Follow the same code for the benchmark, 
but only run one iteration and before the functor returns the final log-pdf variable,
print out the bytesizes for `std::vector` containers responsible for representing the expression graph,
the value and adjoints for each expression node, and other objects needed internally for their system.
Based on the paper, the `ChainableStack::instance_` is a pointer to the global stack object 
capturing all that logic, following the usual singleton pattern.
We took the member variables mentioned in their paper that were responsible for saving the necessary states
(code has slightly changed since the paper and we referred to their github for the current version to get the correct members):

- `stan::math::ChainableStack::instance_->var_stack_.size() * sizeof(element)` 
- `stan::math::ChainableStack::instance_->var_nochain_stack_ * sizeof(element)`
- `stan::math::ChainableStack::instance_->var_alloc_stack_ * sizeof(element)`
- `stan::math::ChainableStack::instance_->memalloc_.bytes_allocated()`
- `total = 4718696`

The latter is the memory pool that the paper refers to as "the arena".
The other stacks are responsible for remembering the AD variables for each expression node.
The last member provided a member function that returns the number of bytes allocated,
but this is only a lower bound, as noted by the comment in their code.
Moreover, for simplicity, we omitted other vectors that saved metadata such as the begin and end pointers 
to the chunks of bytes allocated in the arena.
Hence, the computed "total" bytes allocated by summing the four values is a very rough lower bound.
This also does not take into account of any temporary objects that get created during the AD evaluation.

For FastAD, one can easily compute the memory consumption.
The only memory allocated is the value and adjoint cache that get lazily allocated one-time,
and the stack-allocated expression object itself.
The expression object guarantees to not heap-allocate anything except the case for `ad::for_each, ad::sum, ad::prod`
(iterator version).
Since we have `ad::for_each` in this example, we'll add `(N-1) * sizeof(each_expr)` where `each_expr`
is the expression object for `h[i] += phi * (h[i-1] - mu)`.

- `val_buf.size() * sizeof(double)`
- `adj_buf.size() * sizeof(double)`
- `sizeof(expr)`
- `(N-1) * sizeof(h[i] += phi * (h[i-1] - mu)) = (N-1) * 128`
- `total = 1836216`

This is exact amount of memory allocated minus the program stack.
We computed the total bytesize by adding up each individual bytesize computation
and we chose the last `N = 2^14` for the calculation.
We computed for other `N` as well, but they each grew linearly as `N` increased,
so it is enough to compare the slopes, 
or simply the bytesizes themselves if we accept that `N=0` leads to a total bytesize of `0`.
We see that the rough estimate shows FastAD uses 2.5 times less memory than STAN,
and recall that there are other `std::vector` objects we omitted from the calculation for STAN,
so in reality there's a greater difference.
