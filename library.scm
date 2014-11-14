(define > (lambda (x y) (< y x)))
(define >= (lambda (x y) (not (< x y))))
(define <= (lambda (x y) (not (< y x))))
(define = (lambda (x y) (if (< x y) 0 (not (< y x)))))
(define abs (lambda (x) (if (< x 0) (- 0 x) x)))
(define factorial (lambda (x) (if (< x 2) 1 (* x (factorial (- x 1))))))
(define for-each (lambda (x y) (print(if (not (nullp y)) (apply x (cons (car y) (quote ()))) )) (if (not (nullp (cdr y))) (for-each x (cdr y)))(quote())))

(define list-tail(lambda (tx ty) (if (intp ty) (if (> ty 0) (list-tail (cdr tx) (- ty 1)) (if (< ty 0) () tx)) () )))
(define list-ref (lambda (rx ry) (car (list-tail rx ry))))

(define append (lambda (x y) (if (nullp x) (cons y (quote())) (if (nullp (cdr x)) (cons (car x) (cons y (quote()))) (cons (car x) (append (cdr x) y))))))
(define append-list (lambda (lx ly) (if (nullp ly) lx (append-list (append lx (car ly)) (cdr ly))) )) 
(define reverse (lambda (x) (if (nullp x) x (append (reverse (cdr x)) (car x)))))

(define and (lambda (x y) (if (not x) 0 (if (not y) 0 1) )))
(define or (lambda (x y) (if (not (and (not x) (not y))) 1 0)))

(define equal? (lambda (x y) (if (or (not(listp x)) (not(listp y))) (if (or (or (and(intp x)(intp y)) (and(doublep x)(doublep y))) (and(symbolp x)(symbolp y)) ) (if (= x y) 1 0) 0) (if (nullp x) (if (nullp y) 1 0) (if (not (nullp y)) (if (equal? (car x) (car y)) (equal? (cdr x) (cdr y)) 0) 0)))))

(define assoc (lambda (x y) (if (nullp y) 0 (if (equal? x (car (car y))) (car y) (assoc x (cdr y) ) ) )))

(define op-true (lambda (tproc tlst) (if (nullp tlst) (quote()) (if (tproc (car tlst)) (append (op-true tproc (cdr tlst)) (car tlst)) (op-true tproc (cdr tlst))) ) ))
(define op-false (lambda (fproc flst) (if (nullp flst) (quote()) (if (not(fproc (car flst))) (append (op-false fproc (cdr flst)) (car flst)) (op-false fproc (cdr flst))) ) ))
(define list-partition (lambda (pproc plst) (cons (reverse (op-true pproc plst)) (cons (reverse (op-false pproc plst)) (quote()))  )) )


(define list-sort (lambda (sproc slst)(if (nullp slst) (quote()) (if (nullp (cdr slst)) (cons (car slst) (quote())) (append-list (list-sort sproc (car (list-partition (lambda (m)(if (sproc m (car slst)) 1 0)) slst))) (car (cdr (list-partition (lambda (m) (if (sproc m (car slst)) 1 0)) slst))) )) )))
 
