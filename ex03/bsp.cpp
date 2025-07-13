/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsp.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jramos-a <jramos-a@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 21:34:26 by jramos-a          #+#    #+#             */
/*   Updated: 2025/07/13 21:34:26 by jramos-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Point.hpp"

bool bsp( Point const a, Point const b, Point const c, Point const point) {
	// a,b,c vertices to triangle

	// pooint -> the point to check

	// returns true if point is inside triangle, otherwise false
	// if the point is on an endege return false
	float areaABC = area(a, b, c);
	float areaPBC = area(point, b, c);
	float areaAPC = area(a, point, c);
	float areaABP = area(a, b, point);

	if (areaPBC == 0.0f || areaAPC == 0.0f || areaABP == 0.0f)
		return false;
	const float epsilon = 0.0001f;
	return fabs(areaABC - (areaPBC + areaAPC + areaABP)) < epsilon;
}

#include <sstream>
#include <vector>

std::string drawTriangle(Point const a, Point const b, Point const c, Point const p) {
	const int GRID_SIZE = 20;
	std::vector<std::string> grid(GRID_SIZE, std::string(GRID_SIZE, ' '));

	int ax = static_cast<int>(a.getX().toFloat() / 10.0f * (GRID_SIZE - 1) + 0.5f);
	int ay = static_cast<int>(a.getY().toFloat() / 10.0f * (GRID_SIZE - 1) + 0.5f);

	int bx = static_cast<int>(b.getX().toFloat() / 10.0f * (GRID_SIZE - 1) + 0.5f);
	int by = static_cast<int>(b.getY().toFloat() / 10.0f * (GRID_SIZE - 1) + 0.5f);

	int cx = static_cast<int>(c.getX().toFloat() / 10.0f * (GRID_SIZE - 1) + 0.5f);
	int cy = static_cast<int>(c.getY().toFloat() / 10.0f * (GRID_SIZE - 1) + 0.5f);

	int px = static_cast<int>(p.getX().toFloat() / 10.0f * (GRID_SIZE - 1) + 0.5f);
	int py = static_cast<int>(p.getY().toFloat() / 10.0f * (GRID_SIZE - 1) + 0.5f);

	grid[GRID_SIZE - 1 - ay][ax] = 'A';
	grid[GRID_SIZE - 1 - by][bx] = 'B';
	grid[GRID_SIZE - 1 - cy][cx] = 'C';

	if (px >= 0 && px < GRID_SIZE && py >= 0 && py < GRID_SIZE) {
		if (bsp(a, b, c, p))
			grid[GRID_SIZE - 1 - py][px] = 'P';
		else
			grid[GRID_SIZE - 1 - py][px] = 'p';
	}

	struct Line {
		static void draw(std::vector<std::string> &grid, int x0, int y0, int x1, int y1, int GRID_SIZE) {
			int dx = abs(x1 - x0);
			int dy = abs(y1 - y0);
			int sx = (x0 < x1) ? 1 : -1;
			int sy = (y0 < y1) ? 1 : -1;
			int err = dx - dy;

			while (true) {
				if (grid[GRID_SIZE - 1 - y0][x0] == ' ')
					grid[GRID_SIZE - 1 - y0][x0] = '*';
				if (x0 == x1 && y0 == y1)
					break;
				int e2 = 2 * err;
				if (e2 > -dy) { err -= dy; x0 += sx; }
				if (e2 < dx)  { err += dx; y0 += sy; }
			}
		}
	};

	Line::draw(grid, ax, ay, bx, by, GRID_SIZE);
	Line::draw(grid, bx, by, cx, cy, GRID_SIZE);
	Line::draw(grid, cx, cy, ax, ay, GRID_SIZE);

	std::ostringstream oss;
	for (size_t i = 0; i < grid.size(); ++i) {
		oss << grid[i] << '\n';
	}
	return oss.str();
}
