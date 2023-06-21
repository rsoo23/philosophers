/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsoo <rsoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 22:00:34 by rsoo              #+#    #+#             */
/*   Updated: 2023/06/18 22:00:34 by rsoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Notes:
sem_wait(): 
- if s == 0, it no longer can be decremented, the thread will wait on that semaphore 
- if s > 0, it decrements (s--) and executes
sem_post():
- increments the semaphore (s++) once it is done executing

semphores are basically mutexes with a counter
-: sem_wait()
p: print
+: sem_post()
if sem == 1
T0  | . - p +
T1  | . . . . - p + 
T2  | . . . . . . . - p +
T3  | . . . . . . . . . . - p +
Sem | 1 0 0 1 0 0 1 0 0 1 0 0 1

if sem == 2
T0  | . - p +
T1  | . - p + 
T2  | . . . . - p +
T3  | . . . . - p +
Sem | 2 0 0 2 0 0 2
*/
