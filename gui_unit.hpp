#pragma once

#include <QtWidgets/QWidget>
#include <QtWidgets/QMenu>
#include <QtWidgets/QTableWidget>
#include <QResizeEvent>

#include <memory>
#include <QtWidgets/QFileDialog>

#include "renderer/renderer.hpp"
#include "image/image.hpp"

class gui_threshold_t : public QWidget
{
   Q_OBJECT

public:
   explicit gui_threshold_t( std::shared_ptr<QMenu> & parent, std::shared_ptr<renderer_t> renderer );
   ~gui_threshold_t() override;

   void set_image(std::shared_ptr<image_t> const & image);

private slots:
   void set_min(int val);
   void set_max(int val);

private:
   void resizeEvent(QResizeEvent * event) override;

   void init_menu(std::shared_ptr<QMenu> & parent);
   void init_window();

   std::shared_ptr<QSlider> min_slider_, max_slider_;

   float min_, max_; // original min and max values
   float min_slider_val_, max_slider_val_; // slider min and max values like part of range [0; 1]
   size_t slider_length_;

   float resize_mode_; // don't change min_slider_val_ and max_slider_val_ when resizing for not to accumulate an error

   std::shared_ptr<QAction> threshold_;

   std::shared_ptr<image_t> image_;
   std::shared_ptr<renderer_t> renderer_;
};

class gui_info_t : public QTableWidget
{
   Q_OBJECT

public:
   gui_info_t(std::shared_ptr<QMenu> & parent);

   void set_image( std::shared_ptr<image_t> const & image );

private slots:
   void file_info();

private:
   std::shared_ptr<QAction> file_info_;

   std::shared_ptr<image_t> image_;
};

class gui_open_file_t : public QFileDialog
{
   Q_OBJECT

public:
   explicit gui_open_file_t( std::shared_ptr<QMenu> & parent );

signals:
   void file_selected( QString const & file );

private slots:
   void get_file( QStringList const & files );

private:
   std::shared_ptr<QAction> open_file_;
};