/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapdef.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchae <wchae@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 17:57:45 by wchae             #+#    #+#             */
/*   Updated: 2022/04/28 17:58:02 by wchae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _MAP_DEF_
#define _MAP_DEF_

#define WIDTH 8
#define HEIGHT 8

#define NUM_DIRECTIONS 4

#include "linkedstack.h"
// offset: x, y
static int DIRECTION_OFFSETS[NUM_DIRECTIONS][2] = {
	{0, -1},		// 북쪽
	{1, 0},			// 동쪽
	{0, 1},			// 남쪽
	{-1, 0}			// 서쪽
};

enum PosStatus { NOT_VISIT = 0, WALL = 1 , VISIT = 2  };

void findPath(int mazeArray[HEIGHT][WIDTH], MapPosition startPost, MapPosition endPos, LinkedStack *pStack);
int pushLSMapPosition(LinkedStack *pStack, MapPosition node);
void printMaze(int mazeArray[HEIGHT][WIDTH]);

#endif
