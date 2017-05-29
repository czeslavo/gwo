
# Usage
```
from optimization import *

num_of_eval = 10000
population  = 30
dim = 30
s = grey_wolf_optimizer(function.bent_cigar, calculation_type.lin, calculation_type.lin, num_of_eval, population, -10
0, 100, dim)
print(s.best)
```

```
enum class calculation_type { lin, exp, rand };
```