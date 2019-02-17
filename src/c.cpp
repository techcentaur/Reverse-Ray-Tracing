
// -------------------------------Box----------------------------

Box::Box(Vector3f &translate, Vector3f &scale, Material &m):Object(m){
		// get center; lbh
		Vector3f center = c;

		// make 6 planes: as a cube with center on center

		// do scaling and translate


		Vector3f vt(0, 0, 0); // reference coordianate
		// scale and translate
		Vector3f v1 =  (vt)*scale + translate; 
		Vector3f v2 = (vt+1.0)*scale + translate;
		
		// create normals
		Vector3f n1(-1, 0, 0), n2(0, -1, 0), n3(0, 0, -1);
		Vector3f n4(1, 0, 0), n5(0, 1, 0), n6(0, 0, 1);

		// Transformation t;
		// v2 = t.shearingYAboutX(v2,1);
		// n1 = t.rotateAboutY(n1,-45);
		// n4 = t.rotateAboutY(n4,-45);
		// v2.print();
		// n1.print();
		// n4.print();

		// create all side planes
		Plane p1(v1, n1, m), p2(v1, n2, m), p3(v1, n3, m);
		Plane p4(v2, n4, m), p5(v2, n5, m), p6(v2, n6, m);

		planes.push_back(p1);
		planes.push_back(p2);
		planes.push_back(p3);
		planes.push_back(p4);
		planes.push_back(p5);
		planes.push_back(p6);

		Vector3f recentNormal(0.0, 0.0, 0.0);

		boundPoints.push_back(v1);
		boundPoints.push_back(v2);
}


bool Box::getIntersection(Ray3f &ray, float &t){
	Vector3f closestPoint, closestPointNormal;
	float closestParam;	
	float closestDist = numeric_limits<float>::max();

	// for each plane
	// check that if a ray intersects with it: get intersection point
	// check if it lies inside of the polygon
	// if yes, consider that point and its corresponding normal
	// otherwise, do 

	for(int i=0; i<planes.size(); i++){
		float t1;
		if((planes.at(i)).getIntersection(ray, t1)){
            Vector3f iPoint = ray.origin + ray.direction*t1;
            Vector3f nVector = (planes.at(i)).getNormalOnIntersectionPoint(iPoint, ray);

            Ray tempRay(iPoint, -1*nVector, True);
            int hm = box.howManyIntersection(tempRay);
            if(hm%2 == 0){
            	// even (lies outside the box)
            }
            else{
            	// odd (lies inside the box)
            	if((ray.origin).lengthFrom(iPoint) < closestDist){
            		closestDist = (ray.origin).lengthFrom(iPoint);
            		closestPoint= iPoint;
            		closestPointNormal = nVector;
            		closestParam = t1;
            	}
            }
		}	
	}

	t = closestParam;
	recentNormal = closestPointNormal;

	return true;
}

Vector3f Box::getNormalOnIntersectionPoint(Vector3f &point, Ray3f &ray){
	return recentNormal;
}

void Box::print(){
	cout<<"Not implemented"<<endl;
}
// -------------------------------Box----------------------------


