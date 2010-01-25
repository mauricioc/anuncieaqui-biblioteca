inline int g_mod(int i, int n) { if(i == n) return 0; return i; }
bool in_rect(pt a, pt b, pt c) { 
    return sgn(c.x - min(a.x, b.x)) >= 0 && sgn(max(a.x, b.x) - c.x) >= 0 && 
	   sgn(c.y - min(a.y, b.y)) >= 0 && sgn(max(a.y, b.y) - c.y) >= 0; 
}
bool ps_isects(pt a, pt b, pt c) { return ccw(a,b,c) == 0 && in_rect(a,b,c); }

bool ss_isects(pt a, pt b, pt c, pt d) {
    if (ccw(a,b,c)*ccw(a,b,d) == -1 && ccw(c,d,a)*ccw(c,d,b) == -1) return true;
    return ps_isects(a, b, c) || ps_isects(a, b, d) ||
	   ps_isects(c, d, a) || ps_isects(c, d, b);
}

double p_area(vector<pt>& pol) {
    double ret = 0;
    for(int i = 0; i < pol.size(); i++)
	ret += pol[i] % pol[g_mod(i+1, pol.size())];
    return ret/2;
}

int point_polygon(pt p, vector<pt>& pol) {
    int n = pol.size(), count = 0;

    for(int i = 0; i < n; i++)
    {
	int i1 = g_mod(i+1, n);
	if (ps_isects(pol[i], pol[i1], p)) return -1;
	else if(((sgn(pol[i].y - p.y) == 1) != (sgn(pol[i1].y - p.y) == 1)) && 
	   ccw(pol[i], p, pol[i1]) == sgn(pol[i].y - pol[i1].y)) count++;
    }
    return count % 2;
}

pt parametric_isect(pt p, pt v, pt q, pt w) {
    double t = ((q-p)%w)/(v%w);
    return p + v*t;
}

pt ss_isect(pt p, pt q, pt r, pt s) {
    pt isect = parametric_isect(p, q-p, r, s-r);
    if(ps_isects(p, q, isect) && ps_isects(r, s, isect)) return isect;
    return pt(1/0.0, 1/0.0);
}

pt circumcenter(pt a, pt b, pt c) {
    return parametric_isect((b+a)/2, (b-a)*I, (c+a)/2, (c-a)*I); 
}

bool compy(pt a, pt b) { 
    return cmp(a.y, b.y) ? cmp(a.y, b.y) < 0 : cmp(a.x, b.x) < 0; 
}
bool compx(pt a, pt b) { return a < b; }
