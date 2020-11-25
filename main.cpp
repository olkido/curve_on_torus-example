#include <Eigen/Dense>
#include <igl/curve_on_torus.h>
#include <igl/opengl/glfw/Viewer.h>
#include <igl/opengl/glfw/imgui/ImGuiMenu.h>
#include <random>

// the torus mesh
Eigen::MatrixXd V;
Eigen::MatrixXi F;
// The Viewer
igl::opengl::glfw::Viewer viewer;

int max_i = 5;
std::random_device rd;
std::mt19937 mt(rd());
std::uniform_int_distribution<int> dist_i(1, max_i);
std::uniform_real_distribution<double> dist_r(0,1);

// The parameters to igl::curve_on_torus. See curve_on_torus.h for more details.
double r = .5, R = 1;
int a1=dist_i(mt), a2=dist_i(mt), N=50;
Eigen::RowVector2d p0(dist_r(mt), dist_r(mt));

// The 3D curve
Eigen::Matrix<double,Eigen::Dynamic,3> curve;

// Function to draw curve on the torus
void draw_curve();

// Function to draw torus
void draw_torus();

// Function to generate a torus
void generate_torus(const int nX,
  const int nY,
  Eigen::MatrixXd &V,
  Eigen::MatrixXi &F);


using namespace std;
int main(int argc, char *argv[])
{
  // Seed the random number generator
  srand(time(0));

  // Load parameters
  if (argc >1 )
  {
    r = atof(argv[1]);
    if (argc >2 )
    {
      R = atof(argv[2]);
      if (argc >3 )
      {
        a1 = atoi(argv[3]);
        if (argc >4 )
        {
          a2 = atoi(argv[4]);
          if (argc >5 )
          {
            N = atoi(argv[5]);
            if (argc >6 )
            {
              double p0_x = atof(argv[6]);
              if (argc >7 )
              {
                double p0_y = atof(argv[7]);
                p0<<p0_x, p0_y;
              }
            }
          }
        }
      }
    }
  }

  cout<<r<<" "<< R<<" "<< a1<<" "<< a2<<" "<< N<<" "<< p0 << endl;
  // Plot the mesh
  generate_torus(30, 50, V, F);
  viewer.data().clear(); // this clears all data, including overlays
  viewer.data().set_mesh(V, F); // set the mesh to display

  // Generate and plot the curve
  igl::curve_on_torus( r, R, a1, a2, curve, N, p0);
  draw_curve();

  // olga's color preferences :)
  viewer.data().set_colors(.99*Eigen::RowVector3d::Ones());
  viewer.core().background_color<<1.,1.,1.,1.;
  viewer.data().line_color<<173./255,174./255,103./255,1.;

  // Launch the viewer
  viewer.launch();

}

void generate_torus(const int nX,
  const int nY,
  Eigen::MatrixXd &V,
  Eigen::MatrixXi &F)
{
  Eigen::VectorXd theta = Eigen::VectorXd::LinSpaced(nX, 0,2*M_PI);
  Eigen::VectorXd phi = Eigen::VectorXd::LinSpaced(nY, 0,2*M_PI);

  V.resize(nX*nY,3);
  for (int j =0; j<nX; j++)
    for (int i =0; i<nY; i++)
    {
      double t = theta[j];
      double p = phi[i];
      double x = (R+r*cos(t))*cos(p);
      double y = (R+r*cos(t))*sin(p);
      double z = r*sin(t);
      V.row(j*nY+i) << x, y, z;
    }

  Eigen::VectorXi I_tl;
  I_tl.resize((nY-1)*(nX-1));
  for (int j =0; j<nX-1; j++)
    for (int i =0; i<nY-1; i++)
      I_tl[j*(nY-1)+i] = j*nY+i;

  Eigen::VectorXi I_tr = I_tl.array()+nY;
  Eigen::VectorXi I_bl = I_tl.array()+1;
  Eigen::VectorXi I_br = I_tl.array()+nY+1;

  F.resize(2*(nY-1)*(nX-1),3);
  F << I_tl, I_bl, I_tr,
      I_bl, I_br, I_tr;

}
// Function to draw curve on the torus
void draw_curve()
{
  // Plot the vertices of the curve as points
  Eigen::RowVector3d bb_color(121./255, 165./255, 237./255);
  viewer.data().add_points(curve,bb_color);

  // Plot the edges of the bounding box
  for (unsigned i=0;i<curve.rows()-1; ++i)
    viewer.data().add_edges
    (
      curve.row(i),
      curve.row(i+1),
     bb_color
    );
}
